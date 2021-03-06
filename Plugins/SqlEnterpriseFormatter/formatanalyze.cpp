#include "formatanalyze.h"
#include "parser/ast/sqliteanalyze.h"

FormatAnalyze::FormatAnalyze(SqliteAnalyze* analyze) :
    analyze(analyze)
{
}

void FormatAnalyze::formatInternal()
{
    handleExplainQuery(analyze);
    withKeyword("ANALYZE");

    if (!analyze->database.isNull())
        withId(analyze->database).withIdDot();

    withId(analyze->table).withSemicolon();

}
