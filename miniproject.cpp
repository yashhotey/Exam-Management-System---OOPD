#include <iostream>
#include <vector>
using namespace std;

class question
{
private:
    int quesid;
    string questext;
    string opts[4];
    int ans;
public:

    void addquestion()
    {
        cout<<"enter the question id"<<endl;
        cin>>quesid;
        cin.ignore();
        cout<<"enter the question text"<<endl;
        getline(cin,questext);
        cout<<"enter the options"<<endl;
        for(int i=0;i<4;i++)
        {
            getline(cin,opts[i]);
        }
        cout<<"enter the correct answer index"<<endl;
        cin>>ans;
        cout<<"question has been recorded"<<endl;
    }

    int getid()
    {
        return quesid;
    }

    void disp()
    {
        cout<<questext<<endl;
        for(int i=0;i<4;i++)
        {
            cout<<opts[i];
            cout<<endl;
        }
    }

    int getans()
    {
        return ans;
    }
};

class exam
{
private:
    string examtitle;
    vector <question> ques;
public:

    exam()
    {
        examtitle="--";
    }

    void create()
    {
        int n=0;
        cout<<"enter the name of the exam"<<endl;
        cin>>examtitle;
        int z;
        cout<<"enter the no of questions the exam will have"<<endl;
        cin>>z;
        for(int i=0;i<z;i++)
        {
            question q;
            q.addquestion();
            ques.push_back(q);
        }
    }

    void remquestion()
    {
        int id;
        cout<<"enter the question id to be removed"<<endl;
        cin>>id;

        int remind=-1;
        for(size_t i=0;i<ques.size();i++)
        {
            if(ques[i].getid()==id)
            {
                remind=i;
                break;
            }
        }

        if(remind!=-1)
        {
            ques.erase(ques.begin()+remind);
            cout<<"question has been removed"<<endl;
        }
    }

    void modify()
    {
        int i=0;
        do
        {
        int z;
        cout<<"enter 1.To add question\n2.To remove question\n3.To end modification"<<endl;
        cin>>z;
        cin.ignore();
        switch(z)
        {
        case 1:
            ques[0].addquestion();
            break;
        case 2:
            remquestion();
            break;
        case 3:
            i=1;
            break;
        default:
            cout<<"please enter valid value"<<endl;
            break;
        }
        }while(i==0);
    }


    void dis()
    {
        for(size_t i=0;i<ques.size();i++)
        {
            ques[i].disp();
        }
    }

    string gettitle()
    {
        return examtitle;
    }

    vector<question> getques()
    {
        return ques;
    }

    void examlist(exam e[])
    {
        for(int i=0;i<10;i++)
        {
            cout<<i<<"."<<e[i].examtitle<<endl;
        }
    }

};

class student: protected exam
{
private:
    int sid;
    int score[10];
public:

    student(int x)
    {
        sid=x;
        for (int i = 0; i < 10; i++)
            score[i] = 0;
    }

    void attempt(exam e[])
    {
        string temp;
        cout<<"enter the exam you want to attempt"<<endl;
        cin>>temp;

        int index=-1;
        for(int i=0;i<10;i++)
        {
            if(temp==e[i].gettitle())
            {
                index=i;
                break;
            }
        }

        if(index>=0)
        {
            score[index]=0;

            vector <question> q=e[index].getques();

            cout<<"the exam tittled "<<e[index].gettitle()<<" will begin:"<<endl;
            for(int i=0;i<q.size();i++)
            {
              q[i].disp();
              int a;
              cout<<"enter your answer"<<endl;
              cin>>a;
              if(a==q[i].getans())
              {
                  score[index]++;
              }
            }
            cout<<"you scored "<<score[index]<<" out of "<<q.size()<<endl;
        }
        else
        {
            cout<<"exam with title could not be found"<<endl;
        }
    }

    void result(exam e[])
    {
        string temp;
        cout<<"enter the title of exam whose result you want"<<endl;
        cin>>temp;
        int index=-1;
        for(int i=0;i<10;i++)
        {
            if(temp==e[i].gettitle())
            {
                index=i;
                break;
            }
        }
        if(index>=0)
        {
        vector <question> q=e[index].getques();
        cout<<"socred "<<score[index]<<"out of "<<q.size()<<endl;
        }
        else
        {
            cout<<"exam with title could not be found"<<endl;
        }
    }

    int getsid()
    {
        return sid;
    }

};

class admin: protected exam
{
    int adminid;
public:

    admin(int x)
    {
        adminid=x;
    }

    void getcreate(exam &e)
    {
        e.create();
    }

    void getmodify(exam &e)
    {
        e.modify();
    }

    int getadminid()
    {
        return adminid;
    }
};

class user:protected student,protected admin
{
    string post;
    int examcount;
    int id;
public:

    // Add constructor and call base class constructors
    user() : student(-1), admin(-1) // dummy values for now
    {
        post = "";
        examcount = 0;
        id = -1;
    }

    void login(student s[],admin &a)
    {
        int temp;
        cout<<"enter ID"<<endl;
        cin>>temp;
        for(int i=0;i<10;i++)
        {
            if(temp==s[i].getsid())
            {
                post="student";
                id=i;
                break;
            }
            else if(temp==a.getadminid())
            {
                post="admin";
                break;
            }
            else
            {
                post="fail";
            }
        }
    }

    void task(admin &a,student s[],exam e[])
    {
        if(post=="admin")
        {
            int c=0;
            do
            {
                int z;
                cout<<"welcome admin"<<endl;
                cout<<"enter 1.To create exam\n2.To modify existing exam\n3.To view result of a student\n4.To view exam list\n5.To exit"<<endl;
                cin>>z;
                switch(z)
                {
                case 1:
                    cout<<"assign the exam a number"<<endl;
                    cin>>examcount;
                    a.getcreate(e[examcount]);
                    break;
                case 2:
                    cout<<"enter the number of exam you to be modified"<<endl;
                    cin>>examcount;
                    a.getmodify(e[examcount]);
                    break;
                case 3:
                    int temp,index;
                    cout<<"enter id of student whose result you want to see"<<endl;
                    cin>>temp;
                    index=-1;
                    for(int i=0;i<10;i++)
                    {
                        if(temp==s[i].getsid())
                        {
                            index=i;
                            break;
                        }
                    }
                    if(index>=0)
                    {
                        s[index].result(e);
                    }
                    break;
                case 4:
                    e[0].examlist(e);
                    break;
                case 5:
                    c=1;
                    break;
                default:
                    cout<<"enter valid value"<<endl;
                }
            }while(c==0);
        }
        else if(post=="student")
        {
            cout<<"welcome student"<<endl;
            int c=0;
            do
            {
                int z;
                cout<<"enter 1.To attempt exam\n2.To view result\n3.To view exam list\n4.To exit"<<endl;
                cin>>z;
                switch(z)
                {
                case 1:
                    s[id].attempt(e);
                    break;
                case 2:
                    s[id].result(e);
                    break;
                case 3:
                    e[0].examlist(e);
                    break;
                case 4:
                    c=1;
                    break;
                default:
                    cout<<"enter valid value"<<endl;
                }
            }while(c==0);
        }
    }

    string getpost()
    {
        return post;
    }
};

int main()
{

    exam e[10];
    student s[10]={0,1,2,3,4,5,6,7,8,9};
    admin a(100);
    user u;
    int x=0;
    do
    {
        int z;
        cout<<"enter 1.To login\n2.To exit system"<<endl;
        cin>>z;
        switch(z)
        {
        case 1:
            u.login(s,a);
            if(u.getpost()!="fail")
            {
            u.task(a,s,e);
            }
            else
            {
                cout<<"invalid ID"<<endl;
            }
            break;
        case 2:
            x=1;
            break;
        default:
            cout<<"enter valid value"<<endl;
            break;
        }
    }while(x==0);
    return 0;
}
