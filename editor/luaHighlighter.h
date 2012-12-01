/**
 *
 * File: luaHighlighter.h
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#ifndef LUAHIGHLIGHTER_H
#define LUAHIGHLIGHTER_H

#include <QSyntaxHighlighter>

class LuaHighlighter : public QSyntaxHighlighter
{
public:
    LuaHighlighter(QTextDocument *_doc);

private:
    void highlightBlock(const QString &text);

    struct HighlightingRule
    {
        QRegExp pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;

    QTextCharFormat keywordFormat;
    QTextCharFormat classFormat;
    QTextCharFormat singleLineCommentFormat;
    QTextCharFormat multiLineCommentFormat;
    QTextCharFormat quotationFormat;
    QTextCharFormat functionFormat;
    QTextCharFormat constantFormat;

    // QTextCharFormat m_code;
    // QTextCharFormat m_comments;
    // QRegExp m_commentStart;
    // QRegExp m_commentEnd;
};

#endif // LUAHIGHLIGHTER_H
