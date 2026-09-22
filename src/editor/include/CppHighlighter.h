#pragma once

#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QVector>
#include <QRegularExpression>

class QTextDocument;

class CppHighlighter final : public QSyntaxHighlighter {
    Q_OBJECT

public:
    explicit CppHighlighter(QTextDocument* parent = nullptr);

protected:
    void highlightBlock(const QString& text) override;

private:
    struct Rule {
        QRegularExpression pattern;
        QTextCharFormat format;
    };
    QVector<Rule> m_rules;

    QTextCharFormat m_keywordFormat;
    QTextCharFormat m_typeFormat;
    QTextCharFormat m_commentFormat;
    QTextCharFormat m_stringFormat;
    QTextCharFormat m_numberFormat;
    QTextCharFormat m_preprocessorFormat;
    QTextCharFormat m_functionFormat;

    QRegularExpression m_commentStart;
    QRegularExpression m_commentEnd;
};
