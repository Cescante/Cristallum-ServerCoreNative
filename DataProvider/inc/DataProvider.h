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

enum class DataType
{
    JSON,
    CSV,
};

enum class DataSource
{
    TEXT_FILE,
    RELATIONAL_DATABASE,
    NON_RELATIONAL_DATABASE,
};

enum class DataSourceOperation
{
    READ_THROUGH,
    READ_BACK,
};

class DataProvider
{
    protected:
        DataType _dataType;
        DataSource _dataSource;
    public:
        DataType GetDataType();
        DataSource GetDataSource();
};

#endif 
