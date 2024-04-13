#ifndef __HelloCpp__CTriangle__

#define __HelloCpp__CTriangle__



#include <iostream>

using namespace std;






class CTriangle 

{

public:

    CTriangle(){

        initMembers();

    }

    ~CTriangle(){

        

    }

    CTriangle(int ID0,int ID1,int ID2);

    const short*getArray()const {return m_array;}

    void init(int ID0,int ID1,int ID2);

    short vID(int i)const;

    void setVID(int i,short vID);
	bool getFlag(){return flag;}
	void setFlag(bool f){flag=f;}

protected:

    void initMembers();

public:

    short m_array[3];
	short m_color[3];
	int format;
	bool flag;
	double lightflg;

    

};

#endif /* defined(__HelloCpp__c3dIDTriangle__) */
