/**************************************************************************
**
** This file is part of Qt Creator
**
** Copyright (c) 2012 Nokia Corporation and/or its subsidiary(-ies).
**
** Contact: Nokia Corporation (qt-info@nokia.com)
**
**
** GNU Lesser General Public License Usage
**
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this file.
** Please review the following information to ensure the GNU Lesser General
** Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** Other Usage
**
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**************************************************************************/

#include "aggregate.h"

#include <QWriteLocker>
#include <QDebug>

/*!
    \namespace ExtensionSystem
    \brief The ExtensionSystem namespace contains support for bundling related components,
           such that each component exposes the properties and behavior of the
           other components to the outside.

    Components that are bundled to an Aggregate can be "cast" to each other
    and have a coupled life cycle. See the documentation of ExtensionSystem::Aggregate for
    details and examples.
*/

/*!
    \class ExtensionSystem::Aggregate
    \mainclass
    \threadsafe

    \brief Defines a collection of related components that can be viewed as a unit.

    An Aggregate is a collection of components that are handled as a unit,
    such that each component exposes the properties and behavior of the
    other components in the Aggregate to the outside.
    Specifically that means:
    \list
    \o They can be "cast" to each other (using query and query_all methods).
    \o Their life cycle is coupled, i.e. whenever one is deleted all of them are.
    \endlist
    Components can be of any QObject derived type.

    You can use an Aggregate to simulate multiple inheritance by ExtensionSystem. Assume we have
    \code
        using namespace ExtensionSystem;
        class MyInterface : public QObject { ........ };
        class MyInterfaceEx : public QObject { ........ };
        [...]
        MyInterface *object = new MyInterface; // this is single inheritance
    \endcode
    The query method works like a qobject_cast with normal objects:
    \code
        Q_ASSERT(query<MyInterface>(object) == object);
        Q_ASSERT(query<MyInterfaceEx>(object) == 0);
    \endcode
    If we want 'object' to also implement the class MyInterfaceEx,
    but don't want to or cannot use multiple inheritance, we can do it
    at any point using an Aggregate:
    \code
        MyInterfaceEx *objectEx = new MyInterfaceEx;
        Aggregate *aggregate = new Aggregate;
        aggregate->add(object);
        aggregate->add(objectEx);
    \endcode
    The Aggregate bundles the two objects together.
    If we have any part of the collection we get all parts:
    \code
        Q_ASSERT(query<MyInterface>(object) == object);
        Q_ASSERT(query<MyInterfaceEx>(object) == objectEx);
        Q_ASSERT(query<MyInterface>(objectEx) == object);
        Q_ASSERT(query<MyInterfaceEx>(objectEx) == objectEx);
    \endcode
    The following deletes all three: object, objectEx and aggregate:
    \code
        delete objectEx;
        // or delete object;
        // or delete aggregate;
    \endcode

    ExtensionSystem aware code never uses qobject_cast, but always uses
    ExtensionSystem::query which behaves like a qobject_cast as a fallback.
*/

/*!
    \fn T *ExtensionSystem::component()

    Template method that returns the component with the given type, if there is one.
    If there are multiple components with that type a random one is returned.

    \sa Aggregate::components()
    \sa Aggregate::add()
*/

/*!
    \fn QList<T *> ExtensionSystem::components()

    Template method that returns all components with the given type, if there are any.

    \sa Aggregate::component()
    \sa Aggregate::add()
*/

/*!
    \fn T *ExtensionSystem::query<T *>(Aggregate *obj)
    \internal
*/

/*!
    \fn QList<T *> ExtensionSystem::query_all<T *>(Aggregate *obj)
    \internal
*/

/*!
    \relates ExtensionSystem::Aggregate
    \fn T *ExtensionSystem::query<T *>(QObject *obj)

    Performs a dynamic cast that is aware of a possible Aggregate that \a obj
    might belong to. If \a obj itself is of the requested type then it is simply cast
    and returned. Otherwise, if \a obj belongs to an Aggregate all its components are
    checked, or if it doesn't belong to an Aggregate null is returned.

    \sa Aggregate::component()
*/

/*!
    \relates ExtensionSystem::Aggregate
    \fn QList<T *> ExtensionSystem::query_all<T *>(QObject *obj)

    If \a obj belongs to an Aggregate, all components that can be cast to the given
    type are returned. Otherwise, \a obj is returned if it is of the requested type.

    \sa Aggregate::components()
*/

using namespace ExtensionSystem;

/*!
    \fn Aggregate *Aggregate::parentAggregate(QObject *obj)

    Returns the Aggregate object of \a obj if there is one. Otherwise returns 0.
*/
Aggregate *Aggregate::parentAggregate(QObject *obj)
{
    QReadLocker locker(&lock());
    return aggregateMap().value(obj);
}

QHash<QObject *, Aggregate *> &Aggregate::aggregateMap()
{
    static QHash<QObject *, Aggregate *> map;
    return map;
}

/*!
    \fn QReadWriteLock &Aggregate::lock()
    \internal
*/
QReadWriteLock &Aggregate::lock()
{
    static QReadWriteLock lock;
    return lock;
}

/*!
    \fn Aggregate::Aggregate(QObject *parent)

    Creates a new Aggregate with the given \a parent.
    The \a parent is passed directly passed to the QObject part
    of the class and is not used beside that.
*/
Aggregate::Aggregate(QObject *parent)
    : QObject(parent)
{
    QWriteLocker locker(&lock());
    aggregateMap().insert(this, this);
}

/*!
    \fn Aggregate::~Aggregate()

    Deleting the aggregate automatically deletes all its components.
*/
Aggregate::~Aggregate()
{
    QWriteLocker locker(&lock());
    foreach (QObject *component, m_components) {
        disconnect(component, SIGNAL(destroyed(QObject*)), this, SLOT(deleteSelf(QObject*)));
        aggregateMap().remove(component);
    }
    qDeleteAll(m_components);
    m_components.clear();
    aggregateMap().remove(this);
}

void Aggregate::deleteSelf(QObject *obj)
{
    {
        QWriteLocker locker(&lock());
        aggregateMap().remove(obj);
        m_components.removeAll(obj);
    }
    delete this;
}

/*!
    \fn void Aggregate::add(QObject *component)

    Adds the \a component to the aggregate.
    You can't add a component that is part of a different aggregate
    or an aggregate itself.

    \sa Aggregate::remove()
*/
void Aggregate::add(QObject *component)
{
    if (!component)
        return;
    {
        QWriteLocker locker(&lock());
        Aggregate *parentExtensionSystem = aggregateMap().value(component);
        if (parentExtensionSystem == this)
            return;
        if (parentExtensionSystem) {
            qWarning() << "Cannot add a component that belongs to a different aggregate" << component;
            return;
        }
        m_components.append(component);
        connect(component, SIGNAL(destroyed(QObject*)), this, SLOT(deleteSelf(QObject*)));
        aggregateMap().insert(component, this);
    }
    emit changed();
}

/*!
    \fn void Aggregate::remove(QObject *component)

    Removes the \a component from the aggregate.

    \sa Aggregate::add()
*/
void Aggregate::remove(QObject *component)
{
    if (!component)
        return;
    {
        QWriteLocker locker(&lock());
        aggregateMap().remove(component);
        m_components.removeAll(component);
        disconnect(component, SIGNAL(destroyed(QObject*)), this, SLOT(deleteSelf(QObject*)));
    }
    emit changed();
}
