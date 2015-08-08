/**
 * @author Fang Qiao
 * @file DataProvider_int.h
 * @date date created: Tue Mar 31 13:12:55 PDT 2015
 * @brief
 *
 * Contains external declarations of the DataProvider library.
 *
 * Child classes of DataProvider live here. No code outside of the DataProvider
 * code should need to know the structure of individual DataProviders.
 * 
 * @date last modified: Tue Mar 31 13:12:55 PDT 2015
 * 
 * @bug No known bugs.
 */

#ifndef DATAPROVIDER_INT_H
#define DATAPROVIDER_INT_H


#include <DataProvider/inc/DataProvider.h>

/**
 * @brief
 *
 * The JSONDataProvider class.
 * 
 * Assumes all JSON Objects are one-leveled. Keys are mapped to string values.
 *
 */
class JSONDataProvider : public DataProvider
{
    /*
     * TODO: need utility for number checks:
     * "\\s*[+-]?([0-9]+\\.[0-9]*([Ee][+-]?[0-9]+)?|\\.[0-9]+([Ee][+-]?[0-9]+)?|[0-9]+[Ee][+-]?[0-9]+)"
     */
    public:
        JSONDataProvider( DataType type, DataSourceType sourceType,
            std::string source, DataSourceOperation op,
            std::vector<std::string> keys );
        int GetNext( std::string* dataBuff ) override;
        int GetBatch( int batch_size, std::string** dataBuff ) override;

    private:
        rapidjson::Document document;
};

class CSVDataProvider : public DataProvider
{
    public:
        CSVDataProvider( DataType type, DataSourceType sourceType,
            std::string source, DataSourceOperation op,
            std::vector<std::string> keys );
        int GetNext( std::string* dataBuff ) override;
        int GetBatch( int batch_size, std::string** dataBuff ) override;
};

#endif
