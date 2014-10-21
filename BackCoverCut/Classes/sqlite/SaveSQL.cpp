#include "SaveSQL.h"

#define dbName "Text"

USING_NS_CC;

//データベースを開く
int SaveSQL::sqliteOpen(sqlite3 **db){

    FileUtils *fileUtils = FileUtils::getInstance();
    std::string path = fileUtils->fullPathForFilename(dbName);

    return sqlite3_open(path.c_str(),db);
}

// テーブルからコメントを取り出す
const char *SaveSQL::sqliteGetValueForKey(int textRoot, const char *name, int random){
    
    __String *strValue = NULL;
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    
    if (sqliteOpen(&db) == SQLITE_OK) {
        
        // SQL文の実行
        std::string sql = StringUtils::format("SELECT * FROM DisplayText WHERE human = '%s' AND rank = %d  AND type = %d", name, textRoot, random);
        
        if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL) == SQLITE_OK) {
            int ret = sqlite3_step(stmt);

            if (ret == SQLITE_DONE || ret == SQLITE_ROW) {
                const char *val1 = (const char*)sqlite3_column_text(stmt, 3);
                strValue = __String::create(val1);
                
            }
            sqlite3_reset(stmt);
        }
        sqlite3_finalize(stmt);
    }
    
    sqlite3_close(db);
    
    if (strValue != NULL) {
        return strValue->getCString();
    }
    
    return NULL;
}
