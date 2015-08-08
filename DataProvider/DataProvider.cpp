/**
 * @author Fang Qiao
 * @file DataProvider.cpp
 * @date date created: Tue Mar 31 12:00:18 PDT 2015
 * @brief
 *
 * External API for the DataProvider library.
 * 
 * @date last modified: Tue Mar 31 12:00:18 PDT 2015
 * 
 * @bug No known bugs.
 */

#include <DataProvider/inc/DataProvider_int.h>

/**
 * @brief
 *
 * Accessor for _dataType
 *
 * @returns _dataType
 */
DataType DataProvider::GetDataType()
{
    return _dataType;
}

/**
 * @brief
 *
 * Accessor for _dataSourceType
 *
 * @returns _dataSourceType
 */
DataSourceType DataProvider::GetDataSource()
{
    return _dataSourceType;
}

/**
 * @brief
 *
 * Accessor for _description
 *
 * @returns _description
 */
std::string DataProvider::getDescription()
{
    return _description;
}

std::string DataProvider::GetNextLine()
{
    std::string line;
    switch (_dataSourceType)
    {
        case DataSourceType::TEXT_FILE:
            if (std::getline(_sourceFile, line))
            {
                return line;
            }
            break;
        default: throw "data source type is not implemented yet.";
    }
    
    return "";
}

JSONDataProvider::JSONDataProvider( DataType type, DataSourceType sourceType,
    std::string source, DataSourceOperation op, std::vector<std::string> keys )
    : DataProvider( type, sourceType, source, op, keys )
{
    // TODO: Implement top-level array support: parse first line to check
    // if entire document is an array or object.
    
    //
}

/**
 * @brief
 *
 * Gets the next line of JSON data.
 *
 * Currently only handles a returning a vector of strings.
 *
 * @param dataBuff A preallocated vector of strings used to store the next data
 * @return 
 */
int JSONDataProvider::GetNext( std::string* dataBuff )
{   
    if (NULL == dataBuff)
    {
        return GET_DATA_INVALID_INPUT_BUFFER;
    }

    std::string line = GetNextLine();
    
    if (line.empty())
    {
        return GET_DATA_EOF;
    }

    document.Parse(line.c_str());

    
    
    return GET_DATA_SUCCESS;
}

int JSONDataProvider::GetBatch( int batch_size, std::string** dataBuff )
{
    if (NULL == dataBuff)
    {
        return GET_DATA_INVALID_INPUT_BUFFER;
    }

    if (0 == batch_size)
    {
        // return all the rest
        return GET_DATA_SUCCESS;
    }

    return GET_DATA_SUCCESS;
}

CSVDataProvider::CSVDataProvider( DataType type, DataSourceType sourceType,
    std::string source, DataSourceOperation op, std::vector<std::string> keys )
    : DataProvider( type, sourceType, source, op, keys )
{
    // TODO: Move stream forward by reading headers.
}

int CSVDataProvider::GetNext( std::string* dataBuff )
{
    if (NULL == dataBuff)
    {
        return GET_DATA_INVALID_INPUT_BUFFER;
    }

    return GET_DATA_SUCCESS;
}

int CSVDataProvider::GetBatch( int batch_size, std::string** dataBuff )
{
    if (NULL == dataBuff)
    {
        return GET_DATA_INVALID_INPUT_BUFFER;
    }

    if (0 == batch_size)
    {
        // return as many as we can
        return GET_DATA_SUCCESS;
    }

    return GET_DATA_SUCCESS;
}

DataProvider* DataProvider::GetProvider( DataType type,
    DataSourceType sourceType, std::string source, DataSourceOperation op,
    std::vector<std::string> keys )
{
    switch (type)
    {
        case DataType::JSON:
            return new JSONDataProvider( type, sourceType, source, op, keys );
        case DataType::CSV:
            return new CSVDataProvider( type, sourceType, source, op, keys );
        default: throw "data type is not implemented yet.";
    } 
}

DataProvider::DataProvider( DataType type, DataSourceType sourceType,
    std::string source, DataSourceOperation op, std::vector<std::string> keys )
    : _dataType( type )
    , _dataSourceType( sourceType )
    , _dataSource( source )
    , _operation( op )
    , _dataKeys( keys )
{
    // initialize data source
    switch (_dataSourceType)
    {
        case DataSourceType::TEXT_FILE:
            _sourceFile.open( _dataSource.c_str() );  // TODO: 'rb' for windows.
            break;
        default: throw "data source type is not implemented yet.";
    }

    // Load key indices map.
}

DataProvider::~DataProvider()
{
    switch (_dataSourceType)
    {
        case DataSourceType::TEXT_FILE:
            _sourceFile.close();
            break;
        default: throw "data source type is not implemented yet.";
    }

}

