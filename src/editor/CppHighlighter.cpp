#include "include/CppHighlighter.h"

CppHighlighter::CppHighlighter(QTextDocument* parent)
    : QSyntaxHighlighter(parent)
    , m_commentStart(QStringLiteral("/\\*"))
    , m_commentEnd(QStringLiteral("\\*/"))
{
    m_keywordFormat.setForeground(QColor(QStringLiteral("#c678dd")));
    m_keywordFormat.setFontWeight(QFont::Bold);

    m_typeFormat.setForeground(QColor(QStringLiteral("#61afef")));

    m_commentFormat.setForeground(QColor(QStringLiteral("#5c6370")));
    m_commentFormat.setFontItalic(true);

    m_stringFormat.setForeground(QColor(QStringLiteral("#98c379")));

    m_numberFormat.setForeground(QColor(QStringLiteral("#d19a66")));

    m_preprocessorFormat.setForeground(QColor(QStringLiteral("#e5c07b")));

    m_functionFormat.setForeground(QColor(QStringLiteral("#abb2bf")));
    m_functionFormat.setFontWeight(QFont::Bold);

    const auto addRule = [this](const QString& pattern, const QTextCharFormat& format) {
        m_rules.append(Rule{QRegularExpression(pattern), format});
    };

    // Keywords (C++20)
    static const QStringList keywords = {
        QStringLiteral("\\balignas\\b"), QStringLiteral("\\balignof\\b"),
        QStringLiteral("\\bauto\\b"), QStringLiteral("\\bbreak\\b"),
        QStringLiteral("\\bcase\\b"), QStringLiteral("\\bcatch\\b"),
        QStringLiteral("\\bclass\\b"), QStringLiteral("\\bconcept\\b"),
        QStringLiteral("\\bconst\\b"), QStringLiteral("\\bconsteval\\b"),
        QStringLiteral("\\bconstexpr\\b"), QStringLiteral("\\bcontinue\\b"),
        QStringLiteral("\\bco_await\\b"), QStringLiteral("\\bco_return\\b"),
        QStringLiteral("\\bco_yield\\b"), QStringLiteral("\\bdecltype\\b"),
        QStringLiteral("\\bdefault\\b"), QStringLiteral("\\bdelete\\b"),
        QStringLiteral("\\bdo\\b"), QStringLiteral("\\belse\\b"),
        QStringLiteral("\\benum\\b"), QStringLiteral("\\bexplicit\\b"),
        QStringLiteral("\\bexport\\b"), QStringLiteral("\\bextern\\b"),
        QStringLiteral("\\bfinal\\b"), QStringLiteral("\\bfor\\b"),
        QStringLiteral("\\bfriend\\b"), QStringLiteral("\\bgoto\\b"),
        QStringLiteral("\\bif\\b"), QStringLiteral("\\binline\\b"),
        QStringLiteral("\\bmutable\\b"), QStringLiteral("\\bnamespace\\b"),
        QStringLiteral("\\bnew\\b"), QStringLiteral("\\bnoexcept\\b"),
        QStringLiteral("\\bnullptr\\b"), QStringLiteral("\\boverride\\b"),
        QStringLiteral("\\bprivate\\b"), QStringLiteral("\\bprotected\\b"),
        QStringLiteral("\\bpublic\\b"), QStringLiteral("\\breturn\\b"),
        QStringLiteral("\\brequires\\b"), QStringLiteral("\\bsizeof\\b"),
        QStringLiteral("\\bstatic\\b"), QStringLiteral("\\bstatic_assert\\b"),
        QStringLiteral("\\bstruct\\b"), QStringLiteral("\\bswitch\\b"),
        QStringLiteral("\\btemplate\\b"), QStringLiteral("\\bthis\\b"),
        QStringLiteral("\\bthrow\\b"), QStringLiteral("\\btry\\b"),
        QStringLiteral("\\btypedef\\b"), QStringLiteral("\\btypename\\b"),
        QStringLiteral("\\busing\\b"), QStringLiteral("\\bvirtual\\b"),
        QStringLiteral("\\bvoid\\b"), QStringLiteral("\\bvolatile\\b"),
        QStringLiteral("\\bwhile\\b")
    };
    for (const auto& kw : keywords) {
        addRule(kw, m_keywordFormat);
    }

    // Types
    addRule(QStringLiteral("\\b(int|long|short|char|bool|float|double|unsigned|signed|size_t|uint\\d+_t|int\\d+_t|void|auto)\\b"),
            m_typeFormat);

    // Preprocessor
    addRule(QStringLiteral("^\\s*#[^\\n]*"), m_preprocessorFormat);

    // Strings: "..." and '...'
    addRule(QStringLiteral("\".*?\""), m_stringFormat);
    addRule(QStringLiteral("'.*?'"), m_stringFormat);

    // Numbers
    addRule(QStringLiteral("\\b\\d[\\d'_]*(\\.\\d+)?([eE][+-]?\\d+)?\\b"), m_numberFormat);
    addRule(QStringLiteral("\\b0[xX][0-9a-fA-F']+\\b"), m_numberFormat);

    // // comment (single line)
    addRule(QStringLiteral("//[^\\n]*"), m_commentFormat);

    // Function call: name(
    m_rules.append(Rule{QRegularExpression(QStringLiteral("\\b[A-Za-z_][A-Za-z0-9_]*(?=\\()")),
                           m_functionFormat});
}

void CppHighlighter::highlightBlock(const QString& text)
{
    for (const auto& rule : m_rules) {
        auto it = rule.pattern.globalMatch(text);
        while (it.hasNext()) {
            const auto match = it.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }

    // Multi-line /* ... */ comments
    setCurrentBlockState(0);
    int startIndex = 0;
    if (previousBlockState() != 1) {
        startIndex = text.indexOf(m_commentStart);
    }
    while (startIndex >= 0) {
        const auto endMatch = m_commentEnd.match(text, startIndex);
        int endIndex = endMatch.capturedStart();
        int commentLength = 0;
        if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex + endMatch.capturedLength();
        }
        setFormat(startIndex, commentLength, m_commentFormat);
        startIndex = text.indexOf(m_commentStart, startIndex + commentLength);
    }
}
