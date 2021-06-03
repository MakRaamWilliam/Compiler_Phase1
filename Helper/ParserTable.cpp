
#include "ParserTable.h"
ParserTable* ParserTable::instance = nullptr;

ParserTable::ParserTable() {

}

ParserTable *ParserTable::getInstance() {
    if(instance == nullptr){
        instance = new ParserTable();
    }
    return instance;
}