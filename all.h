#pragma once
#include<iostream>
using namespace std;
struct clAss//选课表
{
    int key;//学号
    int id;//课程号
    int scores;//成绩
    clAss* next = NULL;
 
};

struct clAss_index_table//索引表结构体定义
{
    int key;
    clAss* body;
 
};

void create_clAss_table(clAss*& clAss_head, int k, int ID, int sc)//创建和添加选课表
{
    clAss* p = new clAss;
   
    if (clAss_head == NULL)
    {
        clAss_head = p;
        clAss_head->key = k; clAss_head->id = ID; clAss_head->scores = sc;
         clAss_head->next=NULL;
    }
    else
    {
        clAss* j = clAss_head;
        while (j->next != NULL)
            j = j->next;

        j->next = p;
        p->key = k; p->id = ID; p->scores = sc;
    }
   
}


void Shellsort_clAss_index_table(clAss_index_table R[], int n)//对选课表索引进行希尔排序
{
    int i, j, d;
    clAss_index_table tmp;
    d = n / 2;	  	//增量置初值
    while (d > 0)
    {
        for (i = d; i < n; i++)
        {   //对相隔d位置的元素组直接插入排序
            tmp = R[i];
            j = i - d;
            while (j >= 0 && tmp.key < R[j].key)
            {
                R[j + d] = R[j];
                j = j - d;
            }
            R[j + d] = tmp;
        }
        d = d / 2;	 	//减小增量
    }


}



struct student//student，学生表
{
    int key;//学号
    string name;//姓名
    string size;//性别
    student* lchild, * rchild;
};
struct student_index_table//学生表索引
{
    int S_key;
    string S_name;
 
};
student* InserBST(student* bt, int k, string name, string size)  //插入节点数据and创建树
{
    if (bt == NULL)
    {
        bt = new student;
        bt->key = k; bt->name = name; bt->size = size;
        bt->lchild = bt->rchild = NULL;
    }
    else if (k < bt->key)
        bt->lchild = InserBST(bt->lchild, k, name,size);
    else if (k > bt->key)
        bt->rchild = InserBST(bt->rchild, k, name, size);

    return bt;
}





student* find(const int& key, student* bt)//在二叉排序树中寻找节点
{
    student* p = bt;
    student* f = NULL;//初始化
    while (p != NULL && p->key != key) {//往下搜索
        if (key < p->key) {
            f = p;
            p = p->lchild;
        }
        else {
            f = p;
            p = p->rchild;
        }
    }
    return p;//若数值不存在，则指向NULL结点被返回
}

void Delete(const int& k, student*& p) {
    //在p为根的二叉排序树上删除关键字为k的结点
    student* s, * temp;
    if (p != NULL)
        if (k < p->key)//还没找到p
            Delete(k, p->lchild);//递归地在p的左子树上删除关键字为k的结点
        else if (k > p->key)
            Delete(k, p->rchild);//递归地在p的左子树上删除关键字为k的结点
        else if (p->lchild != NULL && p->rchild != NULL) {//找到p,但是p的左右子树都不空
            //s = Min(p->rchild);
            temp = p->rchild;
            while (temp->lchild != NULL) {
                temp = temp->lchild;
            }//找到p的右子树上最小的数s，替换掉p，然后删掉s
            s = temp;
            p->key = s->key;//将p替换成s
            Delete(s->key, p->rchild);//递归地删掉s
        }
        else {//相等找到,但是左或右为空
            temp = p;
            if (p->lchild == NULL)       p = p->rchild;//左子树空，则将p替换为右子树上第一个结点
            else if (p->rchild == NULL)  p = p->lchild;//右子树空，则将p替换为左子树上第一个结点
            delete temp;
        }
}


//course
struct course//课程表
{
    int id;//课程号
    string course_name;//课程名
    int credits;//学分
    course* next = NULL;
};

struct course_index_table//索引表结构体定义
{
    int key;
    course* body;
    
};
void create_course_table(course*& course_head,  int ID, string c_name, int cr)//创建和添加课程表
{
    course* p = new course;

    if (course_head == NULL)
    {
        course_head = p;
        course_head->id = ID; course_head->course_name = c_name; course_head->credits = cr;
        course_head->next = NULL;
    }
    else
    {
        course* j = course_head;
        while (j->next != NULL)
            j = j->next;

        j->next = p;
        p->id = ID; p->course_name = c_name; p->credits = cr;
    }

}

void Shellsort_course_index_table(course_index_table R[], int n)//对课程表索引进行希尔排序
{
    int i, j, d;
    course_index_table tmp;
    d = n / 2;	  	//增量置初值
    while (d > 0)
    {
        for (i = d; i < n; i++)
        {   //对相隔d位置的元素组直接插入排序
            tmp = R[i];
            j = i - d;
            while (j >= 0 && tmp.key < R[j].key)
            {
                R[j + d] = R[j];
                j = j - d;
            }
            R[j + d] = tmp;
        }
        d = d / 2;	 	//减小增量
    }


}
void Shellsort_student_index_table(student_index_table R[], int n)//对学生表索引进行希尔排序
{
    int i, j, d;
    student_index_table tmp;
    d = n / 2;	  	//增量置初值
    while (d > 0)
    {
        for (i = d; i < n; i++)
        {   //对相隔d位置的元素组直接插入排序
            tmp = R[i];
            j = i - d;
            while (j >= 0 && tmp.S_key < R[j].S_key)
            {
                R[j + d] = R[j];
                j = j - d;
            }
            R[j + d] = tmp;
        }
        d = d / 2;	 	//减小增量
    }


}