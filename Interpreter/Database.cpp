#include "Database.h"

Database::~Database()
{
    for (int i = 0; i < (int)relations.size(); i++) {
        delete relations.at(i);
    }
}
