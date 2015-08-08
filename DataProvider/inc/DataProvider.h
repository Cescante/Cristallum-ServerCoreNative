/**
 * @author Fang Qiao
 * @file DataProvider.h
 * @date date created: Tue Mar 31 12:00:24 PDT 2015
 * @brief
 *
 * Contains the Internal declarations of the DataProvider library.
 * 
 * @date last modified: Tue Mar 31 12:00:24 PDT 2015
 * 
 * @bug No known bugs.
 */

#ifndef DATAPROVIDER_H
#define DATAPROVIDER_H

#include <fstream>
#include <map>
#include <string>
#include <vector>

#include <DataProvider/rapidjson/include/rapidjson/document.h>
#include <DataProvider/rapidjson/include/rapidjson/filereadstream.h>

#define GET_DATA_SUCCESS                0
#define GET_DATA_FAILURE                (-1)
#define GET_DATA_EOF                    1
#define GET_DATA_INVALID_INPUT_BUFFER   2
/**
 * @brief
 *
 * Type of data the DataProvider works with. 
 */
enum class DataType
{
    JSON,       ///< JSON DataProvider
    CSV,        ///< CSV DataProvider
    XML,        ///< all XML format DataProvider
};

/**
 * @brief
 *
 * Type of data source. 
 */
enum class DataSourceType
{
    TEXT_FILE,                  ///< Text file
    RELATIONAL_DATABASE,        ///< Relational database
    NON_RELATIONAL_DATABASE,    ///< TODO: many different kinds
};

/**
 * @brief
 *
 * Type of data source operation
 */
enum class DataSourceOperation
{
    READ_THROUGH,
    READ_BACK,
};

/**
 * @brief
 *
 * The DataProvider class providing data to callers from a data source.
 */
class DataProvider
{
    // TODO: formatting options.
    // TODO: DataProvider should handle conversion to feature vectors based on
    // formatting options, and accept a template type.
    protected:
        DataType _dataType;
        DataSourceType _dataSourceType;
        std::string _dataSource; // should really be a file descriptor or some such.
        DataSourceOperation _operation;
        std::map<std::string, int> _dataKeyMap;
        std::vector<std::string>_dataKeys;
        std::string GetNextLine();
        DataProvider( DataType type, DataSourceType sourceType,
            std::string source, DataSourceOperation op,
            std::vector<std::string> keys );
        
    public:
        DataType GetDataType();
        DataSourceType GetDataSource();
        DataSourceOperation GetOperation();
        std::string getDescription();
        // NOTE: '=0'
        //          - abstract function syntax
        virtual int GetNext( std::string* dataBuff ) =0;
        virtual int GetBatch( int batch_size, std::string** dataBuff ) =0;
        static DataProvider* GetProvider(
                DataType type,
                DataSourceType sourceType,
                std::string source,
                DataSourceOperation op,
                std::vector<std::string> keys );
        ~DataProvider();
        // NOTE: '= delete' on copy constructor and assignment operater
        //          - prohibiting copying syntax.
        DataProvider( const DataProvider& ) = delete;
        DataProvider& operator=( const DataProvider& ) = delete;

    private:
        std::string _description;
        std::ifstream _sourceFile;
};

#endif 
