#include "utilstranslation.h"
#include <QApplication>
#include <QTranslator>
#include <QLocale>
using namespace RadarDisplay;


static UtilsTranslation *g_utilsTranslation = 0;

bool UtilsTranslation::load()
{
    if (g_utilsTranslation)
        return true;
    g_utilsTranslation = new UtilsTranslation;
    g_utilsTranslation->m_translator = new QTranslator;
    bool ret = g_utilsTranslation->m_translator->load(QLocale::system(), "Utils", ".", ":/translations");
    qApp->installTranslator(g_utilsTranslation->m_translator);
    return ret;
}

void UtilsTranslation::unload()
{
    if (!g_utilsTranslation)
        return;
    delete g_utilsTranslation->m_translator;
    delete g_utilsTranslation;
    g_utilsTranslation = 0;
}
