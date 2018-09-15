#ifndef __SQLIST_H__
#define __SQLIST_H__

// - - - - - - 状态码 - - - - - - - - - - - - - - - - - - - - - -   
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;

// - - - - 线性表的动态分配顺序存储结构 - - - - - - - - - - - - - 
#define LIST_INIT_SIZE 100  /* 存储空间初始大小 */
#define LISTINCREMENT 10    /* 存储空间每次的扩大量 */
typedef int ElemType;
typedef struct{
	ElemType *elem;         /* 第一个结点的指针 */ 
	int length;			    /* 顺序表长度 */
	int listsize;		    /* 已分配的存储空间大小 */
}Sqlist;

// - - - - - - 头文件调用 - - - - - - - - - - - - - - - - - - - - 
#include <stdio.h>
#include <stdlib.h>

// - - - - - - 构造空的线性表 - - - - - - - - - - - - - - - - - - 
Status InitList(Sqlist *L)
{
	(*L).elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType) );
	if( !(*L).elem )
		exit(OVERFLOW);
	(*L).length = 0;					 /* 顺序表初始化长度为0 */
	(*L).listsize = LIST_INIT_SIZE;      /* 顺序表初始化内存分配大小 */
	return OK;
}

// - - - - - - 销毁线性表 - - - - - - - - - - - - - - - - - - - - 
void DestroyList(Sqlist *L)
{
	free((*L).elem);	  /* 释放内存 */
	(*L).elem = NULL;	  /* 指针重置为空指针 */
	(*L).length = 0;
	(*L).listsize = 0; 
}

// - - - - - - 重置线性表 - - - - - - - - - - - - - - - - - - - - 
void ClearList(Sqlist *L)
{
	(*L).length = 0;      /* 顺序表长度恢复初始化 */
}

// - - - - - - 判断是否为空表 - - - - - - - - - - - - - - - - - - 
Status ListEmpty(Sqlist L)
{
	if( L.length == 0 )
		return TRUE;
	else
		return FALSE;
}

// - - - - - - 得到线性表长度 - - - - - - - - - - - - - - - - - - 
int ListLength(Sqlist L)
{
	return L.length;
}

Status GetElem(Sqlist L, int i, ElemType *e)
{
	if( (i<1) || (i>L.length) )   /* i超出顺序表的长度范围 */ 
		return ERROR;
	else
		*e = L.elem[i-1];		  /* 得到第i个元素 */
	return OK;
}

// - - - - - - 得到满足关系的元素的位置 - - - - - - - - - - - - - 
int LocateElem(Sqlist L, ElemType e, Status(Compare)(ElemType, ElemType))
{
	int i = 1;
	while( (i<=L.length) && !Compare(e, L.elem[i-1]) )
							  	  /* 数组下标从0开始 */
								  /* 判断第i个元素是否与e满足关系 */
		i++;
	if( i<=L.length )			  /* 判断得到的位置是否超出顺序表的范围 */
		return i;
	else 
		return 0;
}

// - - - - - - 得到前驱元素 - - - - - - - - - - - - - - - - - - -  
Status PriorElem(Sqlist L, ElemType cur_e, ElemType *pre_e)
{
	int i = 1;

	if( L.elem[0] != cur_e )	  /* 第一个结点没有前驱 */
	{
		while( (i<L.length) && (L.elem[i]!=cur_e) )
								  /* 依次判断第i个元素是否与cur_e相等 */
			i++;				
		if( i<L.length )		  /* 判断得到的元素的位置是否超出顺序表的范围 */
		{
			*pre_e = L.elem[i-1]; /* 得到前驱元素 */ 
			return OK;
		}
	}
	return ERROR;
}

// - - - - - - 得到后继元素 - - - - - - - - - - - - - - - - - - - 
Status NextElem(Sqlist L, ElemType cur_e, ElemType *next_e)
{
	int i = 0;
	while( (i<L.length) && (L.elem[i]!=cur_e) )
		i++;
	if( i<L.length )			  /* 最后一个结点没有后继元素 */
								  /* 判断得到的元素的位置是否超出顺序表的范围 */
	{
		*next_e = L.elem[i-1];    /* 得到后继元素 */
		return OK;
	}
	return ERROR;
}

// - - - - - - 在指定位置插入元素 - - - - - - - - - - - - - - - - 
Status ListInsert(Sqlist *L, int i, ElemType e)
{
	ElemType *p, *q;
	ElemType *newbase;
	
	if( (i<1) || (i>(*L).length+1) )   /* i超出顺序表的长度范围 */
		return ERROR;
	if( (*L).length >= (*L).listsize ) /* 顺序表存储空间是否已满 */
	{
		newbase = (ElemType *)realloc( (*L).elem,
						((*L).listsize + LISTINCREMENT) * sizeof(ElemType) );
									   /* 开辟新空间，增加存储空间 */
		if( !newbase )				   /* 开辟空间失败 */
			exit(OVERFLOW);
		(*L).elem = newbase;		   /* 顺序表的新基址 */
		(*L).listsize = (*L).listsize + LISTINCREMENT;
									   /* 顺序表存储空间增加 */
	} 	
	q = &(*L).elem[i-1];			   /* q为新元素的插入位置 */
	for( p=&(*L).elem[(*L).length-1]; p>=q; --p )
		*(p+1) = *p;				   /* 插入位置之后的元素后移 */
	*q = e;							   /* 元素e 插入 */
	(*L).length = (*L).length + 1;     /* 顺序表长度增加 */
	return OK;
}

// - - - - - - 删除指定位置元素 - - - - - - - - - - - - - - - - - 
Status ListDelete(Sqlist *L, int i, ElemType *e)
{
	int k;
	ElemType *p, *q;
	
	if( (i<1) || (i>(*L).length) )     /* i超出顺序表的长度范围 */
		return ERROR;
	p = &(*L).elem[i-1];			   /* p为删除元素的位置 */ 
	*e = *p;						   /* 得到第i个元素 */
	q = (*L).elem + (*L).length - 1;   /* q为表尾元素 */
	for( ++p; p<=q; ++p )
		*(p-1) = *p;				   /* 被删除元素之后的元素前移 */ 
	(*L).length = (*L).length - 1;     /* 顺序表长度减少 */
	return OK;
}

// - - - - - - 对每个元素调用指定函数 - - - - - - - - - - - - - - - 
Status ListTraverse(Sqlist L, void(visit)(ElemType))
{
	int i;
	for( i=0; i<L.length; i++ )        /* 遍历顺序表中的所有元素 */
		visit(L.elem[i]);
}

#endif
