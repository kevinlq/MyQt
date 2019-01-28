#ifndef UTILSTRANSLATION_H
#define UTILSTRANSLATION_H

class QTranslator;
namespace RadarDisplay {
class UtilsTranslation
{
public:
    static bool load();
    static void unload();

private:
    QTranslator *m_translator;
};
} // namespace RadarDisplay
#endif // UTILSTRANSLATION_H
