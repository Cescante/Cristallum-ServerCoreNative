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

DataType DataProvider::GetDataType()
{
    return _dataType;
}

DataSource DataProvider::GetDataSource()
{
    return _dataSource;
}


