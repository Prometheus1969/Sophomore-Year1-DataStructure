#ifndef __SQLIST_H__
#define __SQLIST_H__

// - - - - - - ״̬�� - - - - - - - - - - - - - - - - - - - - - -   
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;

// - - - - ���Ա�Ķ�̬����˳��洢�ṹ - - - - - - - - - - - - - 
#define LIST_INIT_SIZE 100  /* �洢�ռ��ʼ��С */
#define LISTINCREMENT 10    /* �洢�ռ�ÿ�ε������� */
typedef int ElemType;
typedef struct{
	ElemType *elem;         /* ��һ������ָ�� */ 
	int length;			    /* ˳����� */
	int listsize;		    /* �ѷ���Ĵ洢�ռ��С */
}Sqlist;

// - - - - - - ͷ�ļ����� - - - - - - - - - - - - - - - - - - - - 
#include <stdio.h>
#include <stdlib.h>

// - - - - - - ����յ����Ա� - - - - - - - - - - - - - - - - - - 
Status InitList(Sqlist *L)
{
	(*L).elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType) );
	if( !(*L).elem )
		exit(OVERFLOW);
	(*L).length = 0;					 /* ˳����ʼ������Ϊ0 */
	(*L).listsize = LIST_INIT_SIZE;      /* ˳����ʼ���ڴ�����С */
	return OK;
}

// - - - - - - �������Ա� - - - - - - - - - - - - - - - - - - - - 
void DestroyList(Sqlist *L)
{
	free((*L).elem);	  /* �ͷ��ڴ� */
	(*L).elem = NULL;	  /* ָ������Ϊ��ָ�� */
	(*L).length = 0;
	(*L).listsize = 0; 
}

// - - - - - - �������Ա� - - - - - - - - - - - - - - - - - - - - 
void ClearList(Sqlist *L)
{
	(*L).length = 0;      /* ˳����Ȼָ���ʼ�� */
}

// - - - - - - �ж��Ƿ�Ϊ�ձ� - - - - - - - - - - - - - - - - - - 
Status ListEmpty(Sqlist L)
{
	if( L.length == 0 )
		return TRUE;
	else
		return FALSE;
}

// - - - - - - �õ����Ա��� - - - - - - - - - - - - - - - - - - 
int ListLength(Sqlist L)
{
	return L.length;
}

Status GetElem(Sqlist L, int i, ElemType *e)
{
	if( (i<1) || (i>L.length) )   /* i����˳���ĳ��ȷ�Χ */ 
		return ERROR;
	else
		*e = L.elem[i-1];		  /* �õ���i��Ԫ�� */
	return OK;
}

// - - - - - - �õ������ϵ��Ԫ�ص�λ�� - - - - - - - - - - - - - 
int LocateElem(Sqlist L, ElemType e, Status(Compare)(ElemType, ElemType))
{
	int i = 1;
	while( (i<=L.length) && !Compare(e, L.elem[i-1]) )
							  	  /* �����±��0��ʼ */
								  /* �жϵ�i��Ԫ���Ƿ���e�����ϵ */
		i++;
	if( i<=L.length )			  /* �жϵõ���λ���Ƿ񳬳�˳���ķ�Χ */
		return i;
	else 
		return 0;
}

// - - - - - - �õ�ǰ��Ԫ�� - - - - - - - - - - - - - - - - - - -  
Status PriorElem(Sqlist L, ElemType cur_e, ElemType *pre_e)
{
	int i = 1;

	if( L.elem[0] != cur_e )	  /* ��һ�����û��ǰ�� */
	{
		while( (i<L.length) && (L.elem[i]!=cur_e) )
								  /* �����жϵ�i��Ԫ���Ƿ���cur_e��� */
			i++;				
		if( i<L.length )		  /* �жϵõ���Ԫ�ص�λ���Ƿ񳬳�˳���ķ�Χ */
		{
			*pre_e = L.elem[i-1]; /* �õ�ǰ��Ԫ�� */ 
			return OK;
		}
	}
	return ERROR;
}

// - - - - - - �õ����Ԫ�� - - - - - - - - - - - - - - - - - - - 
Status NextElem(Sqlist L, ElemType cur_e, ElemType *next_e)
{
	int i = 0;
	while( (i<L.length) && (L.elem[i]!=cur_e) )
		i++;
	if( i<L.length )			  /* ���һ�����û�к��Ԫ�� */
								  /* �жϵõ���Ԫ�ص�λ���Ƿ񳬳�˳���ķ�Χ */
	{
		*next_e = L.elem[i-1];    /* �õ����Ԫ�� */
		return OK;
	}
	return ERROR;
}

// - - - - - - ��ָ��λ�ò���Ԫ�� - - - - - - - - - - - - - - - - 
Status ListInsert(Sqlist *L, int i, ElemType e)
{
	ElemType *p, *q;
	ElemType *newbase;
	
	if( (i<1) || (i>(*L).length+1) )   /* i����˳���ĳ��ȷ�Χ */
		return ERROR;
	if( (*L).length >= (*L).listsize ) /* ˳���洢�ռ��Ƿ����� */
	{
		newbase = (ElemType *)realloc( (*L).elem,
						((*L).listsize + LISTINCREMENT) * sizeof(ElemType) );
									   /* �����¿ռ䣬���Ӵ洢�ռ� */
		if( !newbase )				   /* ���ٿռ�ʧ�� */
			exit(OVERFLOW);
		(*L).elem = newbase;		   /* ˳�����»�ַ */
		(*L).listsize = (*L).listsize + LISTINCREMENT;
									   /* ˳���洢�ռ����� */
	} 	
	q = &(*L).elem[i-1];			   /* qΪ��Ԫ�صĲ���λ�� */
	for( p=&(*L).elem[(*L).length-1]; p>=q; --p )
		*(p+1) = *p;				   /* ����λ��֮���Ԫ�غ��� */
	*q = e;							   /* Ԫ��e ���� */
	(*L).length = (*L).length + 1;     /* ˳��������� */
	return OK;
}

// - - - - - - ɾ��ָ��λ��Ԫ�� - - - - - - - - - - - - - - - - - 
Status ListDelete(Sqlist *L, int i, ElemType *e)
{
	int k;
	ElemType *p, *q;
	
	if( (i<1) || (i>(*L).length) )     /* i����˳���ĳ��ȷ�Χ */
		return ERROR;
	p = &(*L).elem[i-1];			   /* pΪɾ��Ԫ�ص�λ�� */ 
	*e = *p;						   /* �õ���i��Ԫ�� */
	q = (*L).elem + (*L).length - 1;   /* qΪ��βԪ�� */
	for( ++p; p<=q; ++p )
		*(p-1) = *p;				   /* ��ɾ��Ԫ��֮���Ԫ��ǰ�� */ 
	(*L).length = (*L).length - 1;     /* ˳����ȼ��� */
	return OK;
}

// - - - - - - ��ÿ��Ԫ�ص���ָ������ - - - - - - - - - - - - - - - 
Status ListTraverse(Sqlist L, void(visit)(ElemType))
{
	int i;
	for( i=0; i<L.length; i++ )        /* ����˳����е�����Ԫ�� */
		visit(L.elem[i]);
}

#endif
