#include<iostream>
#include<fstream>
#include"all.h"
using namespace std;

int student_num=0, clAss_num=0, course_num=0;//全局变量

void Delete_clAss_table(clAss*& clAss_head, int key, int ID)//删除选课表的数据
{
    clAss* p = NULL, * q = NULL;
    if (clAss_head == NULL)
        cout << "无数据表！";
    p = clAss_head;
    if (ID == p->id && key == p->key)
    {
        clAss_head = clAss_head->next;
        delete p;
        clAss_num--;
    }
    while ((ID != p->id || key != p->key) && p->next != NULL)
    {
        q = p;
        p = p->next;
    }
    if (ID == p->id && key == p->key)
    {
        q->next = p->next;
        delete p;
        clAss_num--;
    }
}
void Delete_clAss_table_for_student(clAss*& clAss_head, int key)//按照学号删除选课表的数据
//此函数用于，删除学生数据时，处理对选课表造成的影响
{
    
    clAss* p = NULL, * q = NULL;
    if (clAss_head == NULL)
        cout << "无数据表！";
    p = clAss_head;
   goon: if (key == p->key)
    {
        clAss_head = clAss_head->next;
        delete p;
        p = clAss_head;
        clAss_num--;
        goto goon;
    }
    
    while (p->next != NULL)
    {
        if (key != p->key)
        {
            q = p;
            p = p->next;
        }
        if (key == p->key)
        {
            q->next = p->next;
            delete p;
            p = q;
            clAss_num--;
        }
    }
}
void Delete_clAss_table_for_course(clAss*& clAss_head, int ID)//按照课程号删除选课表的数据
//此函数用于，删除课程数据时，处理对选课表造成的影响
{
  
    clAss* p = NULL, * q = NULL;
    if (clAss_head == NULL)
        cout << "无数据表！";
    p = clAss_head;
   goon: if (ID == p->id )
    {
        clAss_head = clAss_head->next;
        delete p;
        clAss_num--;
       p = clAss_head;
       goto goon;
    }
   
    while ( p->next != NULL)
    {
        if (ID != p->id)
        {
            q = p;
            p = p->next;
        }
        if (ID == p->id)
        {
        q->next = p->next;
        delete p;
        p = q;
        clAss_num--;
        }
    }
    
}
void Delete_course_table(course*& course_head, int key)//删除课程数据
{
    course* p = NULL, * q = NULL;
    if (course_head == NULL)
        cout << "无数据表！";
    p = course_head;
    if (key == p->id)
    {
        course_head = course_head->next;
        delete p;
        course_num--;
        p = course_head;
    }
    while (p->next != NULL)
    {
        if (key != p->id)
        {
            q = p;
            p = p->next;
        }
        if (key == p->id)
        {
            q->next = p->next;
            delete p;
            p = q;
            course_num--;
        }
    }
}

void InOrder(student* b) //中序遍历递归，输出学生表的信息
{
    ofstream out("out.txt");
    if (b != NULL)
    {
        InOrder(b->lchild);
        out << b->key << "    " << b->name << "  " << b->size << endl;
        InOrder(b->rchild);
    }
   
}

void main() 
{
    ifstream student_in("student.txt");
    ifstream course_in("course.txt");
    ifstream clAss_in("clAss.txt");//导入三张表的信息
 
    int flag = 0;//标志位，0为文件打开/导入失败，1为成功

    if (student_in && course_in && clAss_in)//检查三个文件是否全部成功打开
    {
        cout << "提示！, 信息导入成功" << endl;
        flag = 1;//表示文件导入成功
    }
    else
    {
       cout<<"警告！, 文件读入/打开错误，请检查文件！"<<endl;
    }
    student* bt = NULL;//学生表的根节点 
    clAss* clAss_head = NULL;//选课表表头
    course* course_head = NULL;//课程表表头
    int k, id, scores, credits;//用来存储输入数据的变量
    string st_name, st_size, course_name;//用来存储输入数据的变量
    
    student_index_table student_index[20];//学生表索引表
    clAss_index_table clAss_index[50];//选课表索引表
    course_index_table course_index[20];//课程表索引表
    
    while (!student_in.eof() && flag == 1)//创建学生表（二叉排序树）
    {
        student_in >> k >> st_name >> st_size;
        bt = InserBST(bt, k, st_name, st_size);
        student_index[student_num].S_key = k;//创建学生表索引
        student_index[student_num].S_name = st_name;
        student_num++;

    }
   
    while (!clAss_in.eof() && flag == 1)//创建选课表（顺序表）
    {
        clAss_in >> k >> id >> scores;
       create_clAss_table(clAss_head,  k, id, scores);
        clAss_num++;
    }

    while (!course_in.eof() && flag == 1)//创建课程表（顺序表）
    {
        course_in >> id >> course_name >> credits;
        create_course_table(course_head, id, course_name, credits);
        course_num++;
    }
    
    //下面，初始化clAss和course的索引表

    clAss* p = new clAss;
    p = clAss_head;
    for (int i = 0; i < clAss_num; i++)//初始化选课表
    {
        clAss_index[i].key = p->key;//这里以选课表中的学号作为关键字
        clAss_index[i].body = p;
        p = p->next;
    }

    course* q = new course;
    q = course_head;
    for (int i = 0; i < course_num; i++)//初始化课程表
    {
        course_index[i].key = q->id;//这里以课程表中的课程代号作为关键字
        course_index[i].body = q;
        q = q->next;
    }

    //下面对课程表和选课表的两个索引表按关键字排序(采用希尔排序)
    Shellsort_course_index_table(course_index, course_num);
    Shellsort_clAss_index_table(clAss_index, clAss_num);

  student_in.close();
    course_in.close();
    clAss_in.close();//关闭文件

goon:while (1) 
 {//菜单栏
    cout << "*******************************************************************************************" << endl;
    cout << "*                                                                                         *" << endl;
    cout << "*                  学     生     成     绩     管     理     系     统                    *" << endl;
    cout << "*                                                                                         *" << endl;
    cout << "*******************************************************************************************" << endl;
    cout << "*                                                                                         *" << endl;
    cout << "*                               1.学生信息的添加/删除                                     *" << endl;
    cout << "*                                                                                         *" << endl;
    cout << "*                               2.课程信息的添加/删除                                     *" << endl;
    cout << "*                                                                                         *" << endl;
    cout << "*                               3.选课信息的添加/删除                                     *" << endl;
    cout << "*                                                                                         *" << endl;
    cout << "*                               4.查询学生成绩                                            *" << endl;
    cout << "*                                                                                         *" << endl;
    cout << "*                               5.查询课程成绩                                            *" << endl;
    cout << "*                                                                                         *" << endl;
    cout << "*                               6.保存并退出                                              *" << endl;
    cout << "*                                                                                         *" << endl;
    cout << "*******************************************************************************************" << endl;
    
    int Flag = 0;//用户操作指示标志，通过判断它的值来判别用户执行的操作
    cout << "请输入你的操作：";
    cin >> Flag;//选择操作
        if (Flag == 1) //学生信息的添加/删除 
        {
            int f=0;//添加删除标志，1为添加，2为删除
            cout << "1.添加，2.删除"; cin >> f;
            int st_key; string st_name, st_size;//存储输入的临时变量
                cout << "请依次输入学生的学号，姓名，性别";
                cin >> st_key >> st_name >> st_size;
            if (f == 1) //添加
            {
                int i;
                for ( i = 0; i < student_num; i++)//在学生表索引表中查找用户输入的学号和姓名
                {
                    if (st_key == student_index[i].S_key || st_name == student_index[i].S_name)//如果学号或姓名已经存在
                    {
                        cout << "学号或姓名已存在，添加失败"<<endl;
                        break;//退出返回主菜单
                    }
                }
                if (i == student_num)//在学生表索引表中没有找到，证明可以添加
                {
                    bt = InserBST(bt, st_key, st_name, st_size);//二叉树添加节点

                    student_index[student_num].S_key = st_key;
                    student_index[student_num].S_name = st_name;//学生表索引表添加节点
                    student_num++;//学生总数+1
                    cout << "添加成功！" << endl;
                }
            }
            else//删除
            {
                int i;
                for (i = 0; i < student_num; i++)//在学生表索引表中查找
                {
                    if (st_key == student_index[i].S_key && st_name == student_index[i].S_name)//如果找到该学生
                    {
                        Delete(st_key, bt);//二叉树删除节点
                        Delete_clAss_table_for_student(clAss_head, st_key);//相应的选课表删除内容
                        cout << "删除成功！" << endl;
                        for (int d = 0; d < student_num; d++) 
                        {
                            if (student_index[d].S_key == st_key && student_index[d].S_name == st_name)//学生表索引表删除内容
                            { 
                                
                                student_index[d].S_key = student_index[student_num-1].S_key;
                                student_index[d].S_name = student_index[student_num-1].S_name;
                                break;
                            }
                        }
                        student_num--;//学生数-1
                        //更新选课表索引表
                        clAss* p = new clAss;
                        p = clAss_head;
                        for (int i = 0; i < clAss_num; i++)
                        {
                            clAss_index[i].key = p->key;//这里以选课表中的学号作为关键字
                            clAss_index[i].body = p;
                            p = p->next;
                        }
                        break;//返回主菜单
                    }
                }
                if (i == student_num)//在学生表索引中找不到该学生
                {
                    cout << "该学生不存在，无法删除！" << endl;
                }
            } 
            //输出当前学生表结果
            cout << "学生表" << endl;
            cout << "学号  姓名  性别" << endl;
            student* st;
            Shellsort_student_index_table(student_index, student_num);//对学生索引表排序，保证输出是顺序的
            for (int i = 0; i < student_num; i++)
            {
                cout << student_index[i].S_key << "     " << student_index[i].S_name << "  ";//从学生表中输出学号和名字
                st = find(student_index[i].S_key, bt);//在二叉树中查找性别
                if (st != NULL)cout << st->size << endl;
            }
            cout << endl;
            goto goon;//该操作完成，返回主菜单判断用户的其他操作
        }
        if (Flag == 2) //课程表的添加和删除
        {
            int f = 0;//添加删除标志，1为添加，2为删除
            cout << "1.添加，2.删除"; cin >> f;
            int c_id,c_credits; string c_name;//临时变量
            cout << "请依次输入课程的课程号，课程名，学分";
            cin >>c_id >> c_name >> c_credits;
            if (f == 1)
            {
                int i;
                for (i = 0; i < course_num; i++)
                {
                    if (c_id == course_index[i].key )//在课程表索引表中查找用户输入的课程号
                    {
                        cout << "课程已存在，添加失败"<<endl;
                        break;
                    }
                }
                if (i == course_num)//在课程表索引表中没有找到，证明可以添加
                {
                    create_course_table(course_head, c_id, c_name, c_credits); //添加课程表数据
                    course_index[course_num].key = c_id;//更新课程表索引

                    course* w = NULL; w = course_head;
                    for (int e = 0; e < course_num+1; e++)//使新的选课表索引指向新的数据
                    {
                        if (w->next == NULL)
                        {
                            course_index[course_num].body = w;
                            break;
                        }
                        else
                            w = w->next;
                    }
                     course_num++;//课程数+1
                    cout << "添加成功！"<<endl;
                }
            }
            else//删除
            {
                int i;
                for (i = 0; i < course_num; i++)//在课程表索引表中查找
                {
                    if (c_id == course_index[i].key )//如果找到该课程
                    {
                        cout << "删除成功！" << endl;;
                        for (int d = 0; d < course_num; d++) 
                        {
                            Delete_clAss_table_for_course(clAss_head, c_id);//删除链表节点
                            if (course_index[d].key == c_id)//找到索引表中的相应元素删除
                            {
                                course_index[d].key = course_index[course_num].key;
                                course_index[d].body = course_index[course_num].body;
                                break;//因为课程只有一个，删除完一次之后就可以退出循环了
                            }
                        } 
                        Delete_course_table(course_head, c_id);//相应的选课表删除内容
                        course_num--;//课程数-1
                        //更新选课索引表
                        clAss* p = new clAss;
                        p = clAss_head;
                        for (int i = 0; i < clAss_num; i++)
                        {
                            clAss_index[i].key = p->key;//这里以选课表中的学号作为关键字
                            clAss_index[i].body = p;
                            p = p->next;
                        }
                        break;
                    }
                }
                if (i == course_num)//在课程表索引中找不到该课程
                {
                    cout << "该课程不存在，无法删除！"<<endl;               
                }
                //输出此时课程表的结果
            cout << "课程表" << endl;
            cout << "课程号  课程名          学分" << endl;
            Shellsort_course_index_table(course_index, course_num);//先对课程表索引希尔排序
            course* p = NULL,*r=course_head;
            while (r != NULL)
            { 
                p = r;
                cout << p->id << "       " << p->course_name << "  " << p->credits << endl;
                r = r->next;
            }
            cout << endl;
            goto goon;//返回主菜单
        }
        if (Flag == 3)//选课信息的添加/删除
        {
            int f = 0; // 添加删除标志，1为添加，2为删除
            cout << "1.添加，2.删除"; cin >> f;
            int st_key, c_id,c_scores;//临时变量
            cout << "请依次输入所选课程的学号，课程号，成绩";
            cin >> st_key>>c_id >> c_scores ;
            if (f == 1)//添加
            {
                int i;
                for (i = 0; i < clAss_num; i++)//在选课表索引表中查找用户输入的学号和课程号
                {
                    if (st_key == clAss_index[i].key&&c_id==clAss_index[i].body->id)
                    {
                        cout << "选课项目已存在，添加失败"<<endl;
                        break;
                    }
                }
                if (i == clAss_num)//在选课表索引表中没有找到，证明可以添加
                {
                    create_clAss_table(clAss_head, st_key, c_id, c_scores);//添加选课表数据
                    clAss_index[clAss_num].key = st_key;//更新选课表索引
                    clAss* w = NULL;  w =  clAss_head;
                    for (int e = 0; e < clAss_num+1; e++)//使新的选课表索引指向新的数据
                    {
                        if (w->next == NULL)
                        {
                            clAss_index[clAss_num].body = w;
                            break;
                        }
                        else
                            w = w->next;
                    }
                     clAss_num++;
                    cout << "添加成功！"<<endl;
                }               
            }
            else//删除
            {
                int i;
                for (i = 0; i < clAss_num; i++)//在选课表索引表中查找
                {
                    if (st_key == clAss_index[i].key&&c_id==clAss_index[i].body->id)//如果找到该项目
                    {
                        cout << "删除成功！"<<endl;
                        for (int d = 0; d < clAss_num; d++) {
                            if (clAss_index[d].key == st_key&&clAss_index[d].body->id==c_id)//索引表删除内容
                            {
                                clAss_index[d].key = clAss_index[clAss_num].key;
                                clAss_index[d].body = clAss_index[clAss_num].body;
                                break;
                            }
                        }
                        Delete_clAss_table(clAss_head, st_key, c_id);//选课表删除内容
                         clAss_num--;//选课数-1
                        break;
                    }
                }
                if (i == course_num)//在选课表索引中找不到该项目
                {
                    cout << "该选课项目不存在，无法删除！"<<endl;

                }
                
            }
            //输出当前选课表的结果
            cout << "选课表" << endl;
            cout << "学号  课程号  分数" << endl;
            Shellsort_clAss_index_table(clAss_index, clAss_num);//对索引表希尔排序
            clAss* q = NULL,*u=clAss_head;
            while (u != NULL)
            {
                q = u;
                cout << q->key << "     " << q->id << "        " << q->scores << endl;
                u = u->next;
            }
            cout << endl;
            goto goon;//返回
        }
        if (Flag == 4)//学生姓名查成绩
        {
            string st_name; int kkk,total_s=0,total_n=0;///kkk学号（关键字）
            //total_s=总分数累加。tolal_n=总课程数
            cout << "请输入学生的姓名：";
            cin >> st_name;
            int d = 0;
            for (d; d < student_num; d++)//从学生表索引中搜索该学生并获取学号
            {
                if (student_index[d].S_name == st_name)
                    kkk = student_index[d].S_key;//得到学号
            }
            if (d == student_num+1)//找不到该学生
            {
                cout << "该学生不存在"<<endl;
                goto goon;
            }
            else //找到学生，开始获取成绩
            {
                for (int x = 0; x < clAss_num; x++)//按学号在选课表里找选课的项目
                {
                    if (clAss_index[x].key == kkk)
                    {
                        for (int j = 0; j < course_num; j++)//按照选课表中的项目的课程号，在课程表中找到课程名
                        {
                            if (course_index[j].key == clAss_index[x].body->id)//都找到之后输出课程名和成绩
                            {
                                cout << course_index[j].body->course_name << "   " << clAss_index[x].body->scores << endl;
                                total_s+= clAss_index[x].body->scores;
                                total_n++;//累加求平均值
                            }
                        }
                    }
                }
                cout << "平均成绩为：" << total_s / total_n << endl;//平均值
            }
            int lll = 0;
            cout << "输入1返回主界面：";
            cin >> lll;
            if (lll == 1)goto goon;
            else break;
        }
        if (Flag == 5)//按照课程查成绩
        {
            string cl_name; int kkk, total_s = 0,total_n=0;
            cout << "请输入课程的名称：";
            cin >> cl_name;
            int d = 0;
            for (d; d < course_num; d++)//在课程表索引中找
            {
                if (course_index[d].body->course_name == cl_name)//找到该课程并获取课程号
                {
                    kkk = course_index[d].key;
                    break;
                }
            }
            if (d == course_num)//找不到该课程
            {
                cout << "该课程不存在"<<endl;
                goto goon;
            }
            else//下面输出课程成绩
            {
                for (int x = 0; x < clAss_num; x++)//选课表里找该课程号对应的项目
                {
                    if (clAss_index[x].body->id == kkk)
                    {
                        for (int j = 0; j < student_num; j++)//找到该项目对应的学生的姓名
                        {
                            if (student_index[j].S_key == clAss_index[x].key)//输出相应内容
                            {
                                cout << student_index[j].S_name << "   " << clAss_index[x].body->scores << endl;
                                total_s += clAss_index[x].body->scores;
                                total_n++;//累加
                            }
                        }
                    }
                }
                cout << "平均成绩为：" << total_s / total_n << endl;//平均数
            }
            int lll = 0;
            cout << "输入1返回主界面：";
            cin >> lll;
            if (lll == 1)goto goon;
            else break;

        }
        if (Flag == 6)//导出到文件
        {
            ofstream out("out.txt");//打开文件
            out << "学生表" << endl;
            out << "学号  姓名  性别" << endl;
            student* st;
            Shellsort_student_index_table(student_index, student_num);//学生表索引排序
            for (int i = 0; i < student_num; i++)//输出学生表
            {
                out << student_index[i].S_key << "     " << student_index[i].S_name << "  ";
                st = find(student_index[i].S_key, bt);
                if (st != NULL)out << st->size << endl;
            }
            out << endl;
            out << "课程表" << endl;
            out << "课程号  课程名          学分" << endl;
            Shellsort_course_index_table(course_index, course_num);//课程表索引排序
            course* p = NULL;
            while (course_head != NULL)//输出课程表
            {
                    p = course_head;
                    out << p->id << "       " << p->course_name << "  " << p->credits << endl;
                    course_head = course_head->next;                              
            }
            out << endl;
            out << "选课表" << endl;
            out << "学号  课程号  分数" << endl;
            Shellsort_clAss_index_table(clAss_index, clAss_num);//选课表索引排序
            clAss* q = NULL;
            while (clAss_head != NULL)//输出选课表
            {
                q = clAss_head;
                out << q->key << "     " << q->id << "        " << q->scores << endl;
                clAss_head = clAss_head->next;
            }
            cout << "已退出";
            out.close();
            break;        
        }
    }
}


