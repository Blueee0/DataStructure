#pragma once
//函数结果状态代码
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;			//Status 是函数的类型，其值是函数结果状态代码
typedef char QElemType;		//队列数据类型