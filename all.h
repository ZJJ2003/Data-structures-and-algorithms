#pragma once
#include<iostream>
using namespace std;
struct clAss//ѡ�α�
{
    int key;//ѧ��
    int id;//�γ̺�
    int scores;//�ɼ�
    clAss* next = NULL;
 
};

struct clAss_index_table//������ṹ�嶨��
{
    int key;
    clAss* body;
 
};

void create_clAss_table(clAss*& clAss_head, int k, int ID, int sc)//���������ѡ�α�
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


void Shellsort_clAss_index_table(clAss_index_table R[], int n)//��ѡ�α���������ϣ������
{
    int i, j, d;
    clAss_index_table tmp;
    d = n / 2;	  	//�����ó�ֵ
    while (d > 0)
    {
        for (i = d; i < n; i++)
        {   //�����dλ�õ�Ԫ����ֱ�Ӳ�������
            tmp = R[i];
            j = i - d;
            while (j >= 0 && tmp.key < R[j].key)
            {
                R[j + d] = R[j];
                j = j - d;
            }
            R[j + d] = tmp;
        }
        d = d / 2;	 	//��С����
    }


}



struct student//student��ѧ����
{
    int key;//ѧ��
    string name;//����
    string size;//�Ա�
    student* lchild, * rchild;
};
struct student_index_table//ѧ��������
{
    int S_key;
    string S_name;
 
};
student* InserBST(student* bt, int k, string name, string size)  //����ڵ�����and������
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





student* find(const int& key, student* bt)//�ڶ�����������Ѱ�ҽڵ�
{
    student* p = bt;
    student* f = NULL;//��ʼ��
    while (p != NULL && p->key != key) {//��������
        if (key < p->key) {
            f = p;
            p = p->lchild;
        }
        else {
            f = p;
            p = p->rchild;
        }
    }
    return p;//����ֵ�����ڣ���ָ��NULL��㱻����
}

void Delete(const int& k, student*& p) {
    //��pΪ���Ķ�����������ɾ���ؼ���Ϊk�Ľ��
    student* s, * temp;
    if (p != NULL)
        if (k < p->key)//��û�ҵ�p
            Delete(k, p->lchild);//�ݹ����p����������ɾ���ؼ���Ϊk�Ľ��
        else if (k > p->key)
            Delete(k, p->rchild);//�ݹ����p����������ɾ���ؼ���Ϊk�Ľ��
        else if (p->lchild != NULL && p->rchild != NULL) {//�ҵ�p,����p����������������
            //s = Min(p->rchild);
            temp = p->rchild;
            while (temp->lchild != NULL) {
                temp = temp->lchild;
            }//�ҵ�p������������С����s���滻��p��Ȼ��ɾ��s
            s = temp;
            p->key = s->key;//��p�滻��s
            Delete(s->key, p->rchild);//�ݹ��ɾ��s
        }
        else {//����ҵ�,���������Ϊ��
            temp = p;
            if (p->lchild == NULL)       p = p->rchild;//�������գ���p�滻Ϊ�������ϵ�һ�����
            else if (p->rchild == NULL)  p = p->lchild;//�������գ���p�滻Ϊ�������ϵ�һ�����
            delete temp;
        }
}


//course
struct course//�γ̱�
{
    int id;//�γ̺�
    string course_name;//�γ���
    int credits;//ѧ��
    course* next = NULL;
};

struct course_index_table//������ṹ�嶨��
{
    int key;
    course* body;
    
};
void create_course_table(course*& course_head,  int ID, string c_name, int cr)//��������ӿγ̱�
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

void Shellsort_course_index_table(course_index_table R[], int n)//�Կγ̱���������ϣ������
{
    int i, j, d;
    course_index_table tmp;
    d = n / 2;	  	//�����ó�ֵ
    while (d > 0)
    {
        for (i = d; i < n; i++)
        {   //�����dλ�õ�Ԫ����ֱ�Ӳ�������
            tmp = R[i];
            j = i - d;
            while (j >= 0 && tmp.key < R[j].key)
            {
                R[j + d] = R[j];
                j = j - d;
            }
            R[j + d] = tmp;
        }
        d = d / 2;	 	//��С����
    }


}
void Shellsort_student_index_table(student_index_table R[], int n)//��ѧ������������ϣ������
{
    int i, j, d;
    student_index_table tmp;
    d = n / 2;	  	//�����ó�ֵ
    while (d > 0)
    {
        for (i = d; i < n; i++)
        {   //�����dλ�õ�Ԫ����ֱ�Ӳ�������
            tmp = R[i];
            j = i - d;
            while (j >= 0 && tmp.S_key < R[j].S_key)
            {
                R[j + d] = R[j];
                j = j - d;
            }
            R[j + d] = tmp;
        }
        d = d / 2;	 	//��С����
    }


}