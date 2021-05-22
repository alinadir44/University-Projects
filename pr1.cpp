#include<iostream>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#include<cstdio>
#include<string.h>
#include<cctype>
#include<ctime>
#include<windows.h>
#include<vector>
using namespace std;

//struct to store property address
typedef struct Address{
char city[50],zip[50];
char area[50],street[50],block[50];
}address;

//struct to store construction and purchase dates for property
typedef struct date{
	int d,m,y;
}Date;

//searches string array for 3rd argument passed
int searcharr(char arr[][50],int size,char *str)
{
	int found=0;
	for(int i=0;i<size;i++)
	{
		if(strcmp(arr[i],str)==0)
		{
			found=1;
			break;
		}
		else
		found=0;
	}
	if(found==1)
	return 1;
	else
	return 0;
}

int ViewProperties();
int checkpass(char *str);
//base class of PROPERTY hierarchy
class property{
	protected:
	//int totalproperties;
	int wishlisted[50];
	int propertyid;
	int ownerid;
	int sellerid;
	char  pname[150];
	float psize;
	float baserate;
	float monthrent;
	char owner_name[50];
	char seller_name[50];
	char purchasetype;//b(buy),r(rent)
	address paddress;
	int proptype;//house1,flat2,comm3
	char popularity;//l or h
	float servicefee;
	//contract pcontract;
	char roadfacing;//y,n
	Date constructiondate;
	Date purchasedate;
	char constype;//old or new
	int available;//1 or 0
	float propertyrent;
	float tax;
	public:
	property()
	{
		psize=0;
		baserate=0;
		servicefee=0;
		popularity='l';
		monthrent=0;
		propertyrent=0;
		tax=0;
		for(int i=0;i<50;i++)
		{
			wishlisted[i]=0;
		}
	}
	~property()
	{
	}
	//view either buy or lease type contract
	//argument specifies purchasetype attribute (buy or rent)
	void viewcontract(char pt)
	{
		cout<<"\n*******PROPERTY CONTRACT*******\n";
		if(tolower(pt)=='b')
		{
		
			cout<<"\n\nSelling Party: \nAgent Name: "<<this->seller_name<<"\nAgent ID: AG1-"<<this->sellerid<<endl;
			cout<<"\n\nLump sum to be paid: Rs. "<<this->baserate;
			cout<<"\nTax applicable: Rs. "<<this->tax;
			cout<<"\n\nDate of purchase: "<<purchasedate.d<<"/"<<purchasedate.m<<"/"<<purchasedate.y<<endl;
		}
		else
		{
			cout<<"\n\nSelling Party: \nAgent Name: "<<this->seller_name<<"\nAgent ID: AG1-"<<this->sellerid<<endl;
			if(baserate<=5000000)
			cout<<"\n\nMonthly Payments:\nRent per month (adjustable): "<<this->monthrent<<"\nContract Duration: 3 years minimum\n";
			else
			cout<<"\n\nMonthly Payments:\nRent per month (adjustable): "<<this->monthrent<<"\nContract Duration: 5 years minimum\n";
			cout<<"\n\nDate of purchase: "<<purchasedate.d<<"/"<<purchasedate.m<<"/"<<purchasedate.y<<endl;
		}
	}
	//displays a rented property's rent history
	//only applicable for 'r' purchasetype
	void displayRentHistory()
	{
		float cc=0;
		cout<<"\nMonthly rent: Rs. "<<monthrent<<endl;
		cout<<"\nRent History: \n";
		cc=propertyrent/monthrent;
		if(cc=0)
		cout<<"\nNo prior rent history for this property\n\n";
		else
		{
			for(int i=1;i<=cc;i++)
			{
				cout<<"Month "<<i<<": Rs. "<<monthrent<<endl;
			}
			cout<<endl;
		}
	}
	//display all property attributes conditionally 
	void displaydetails() const
	{
		Sleep(300);
		cout<<"\n\nPROPERTY DETAILS: ";
		Sleep(300);
		cout<<"\n\nProperty Name: "<<pname<<"\nOwner Name: "<<owner_name<<"\nOwner ID: "<<this->ownerid<<"\nSeller Name: "<<seller_name<<"\nSeller ID: "<<this->sellerid;
		cout<<"\nProperty ID: "<<this->propertyid;
		Sleep(300);
		if(tolower(purchasetype)=='b')
		{
			cout<<"\nPurchase type: Buy";
		}
		else
		{
			if(available==0)
			{
				float cc=0;
				Sleep(300);
				cout<<"\nPurchase type: Rent\nMonthly rent: Rs. "<<monthrent<<endl;
				cout<<"\nRent History: \n";
				cc=propertyrent/monthrent;
				if(cc==0)
				cout<<"\nNo prior rent history for this property\n\n";
				else
				{
					for(int i=1;i<=cc;i++)
					{
						Sleep(300);
						cout<<"Month "<<i<<": Rs. "<<monthrent<<endl;
					}
					cout<<endl;
				}	
			}
			else
			{
				cout<<"\nPurchase type: Rent";
			}		
		}
		Sleep(300);
		if(available==0)
		{
			cout<<"\nAvailable: NO\n";
		}
		else
		{
			cout<<"\nAvailable: YES\n";
		}
		Sleep(150);
		//cout<<"\nProperty Size: "<<psize<<" Sq. Guz\nBuyable Rate: Rs. "<<baserate<<"\nTax applicable: "<<tax;
		printf("\n\nProperty Size: %.2f Sq. Guz\nBuyable Rate: Rs. %.2f\nTax applicable: Rs. %.2f",psize,baserate,tax);
		Sleep(150);
		cout<<"\n\nAddress: \nCity: "<<paddress.city<<"\nArea: "<<paddress.area<<"\nBlock: "<<paddress.block<<"\nStreet: "<<paddress.street<<"\nZIP code: "<<paddress.zip;
		Sleep(250);
		if(proptype==1)
		cout<<"\nProperty Type: House\n";
		else if(proptype==2)
		cout<<"\nProperty Type: Flat\n";
		else if(proptype==3)
		cout<<"\nProperty Type: Commercial\n";
		Sleep(300);
		if(tolower(popularity)=='h')
		cout<<"\nPopularity: High\n";
		else
		cout<<"\nPopularity: Low\n";
		Sleep(250);
		cout<<"\nService Fee: "<<((servicefee-1)*100)<<"%";
		Sleep(300);
		if(tolower(roadfacing)=='y')
		cout<<"\nRoad Facing: Yes\n";
		else
		cout<<"\nRoad Facing: No\n";
		Sleep(300);
		if(tolower(constype)=='n')
		cout<<"\nConstruction Type: New\n";
		else
		cout<<"\nConstruction Type: Old\n";
		Sleep(300);
		cout<<"\nDate of construction: "<<constructiondate.d<<"/"<<constructiondate.m<<"/"<<constructiondate.y<<"\n\n";
	}
	
	//function to add a customer id to wishlist
	//checks whether id already exists or not
	//prevents redundancy
	int addto_wishlist(int cuid)
	{
		int found=0,fo1=0;
		for(int i=0;i<50;i++)
		{
			if(wishlisted[i]==0)
			{
				if(searchlist(cuid)==0)
				{
				wishlisted[i]=cuid;
				found=1;
				break;
				}
				else
				{
					fo1=1;
					found=0;
					break;
				}
			}
			else
			{			
			found=0;
			}
		}
		if(found==1)
		{
			cout<<"\n\nSuccessfully added property to your wishlist\n\n";
			return 1;
		}
		else
		{
			cout<<"\nProperty can not be added to wishlist at this time\n\n";
			if(fo1==1)
			{
				cout<<"\nProperty already added to wishlist.\n\n";
			}
			return 0;	
		}
		
	}
	
	//searches property wishlist array for customer id
	int searchlist(int cusid)
	{
		int found=0;
		for(int i=0;i<50;i++)
		{
			if(wishlisted[i]==cusid)
			{
				found=1;
				break;
			}
			else
			found=0;
		}
		if(found==1)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	//setters + getters
	void set_paddress(address p1)
	{
		paddress=p1;
	}
	address get_paddress()
	{
		return paddress;
	}
	
	void set_ownername(char *str)
	{
		strcpy(owner_name,str);
	}
	void set_sellername(char *str)
	{
		strcpy(seller_name,str);
	}
	
	void set_purchasetype(int pt)
	{
		purchasetype=pt;
	}
	int get_purchasetype()
	{
		return purchasetype;
	}
	
	int getAvailable()
	{
		return available;
	}
	
	float get_Baserate()
	{
		return baserate;
	}
	
	char* get_ownername()
	{
		return owner_name;
	}
	char* get_sellername()
	{
		return seller_name;
	}
	
	char* getCity()
	{
		return paddress.city;
	}
	
	float get_psize()
	{
		return psize;
	}
	
	int get_propertyid()
	{
		return propertyid;
	}
	void set_propertyid(int argid)
	{
		propertyid=argid;
	}
	int get_ownerid()
	{
		return ownerid;
	}
	void set_ownerid(int oid)
	{
		ownerid=oid;
	}
	int get_sellerid()
	{
		return sellerid;
	}
	void set_sellerid(int oid)
	{
		sellerid=oid;
	}
	char* get_pname()
	{
		return pname;
	}
	void set_pname(char *pstr)
	{
		strcpy(pname,pstr);
	}
	
	//function to get all property details from user
	//updates baserate attribute with choices 
	void inputdetails()
	{
		available=1;//property must be initially available for purchase or viewing
		cout<<"\nEnter Property Name: ";
		fflush(stdin);
		cin.getline(pname,150);
		cout<<"\nEnter Property Size in Square Guz: ";
		fflush(stdin);
		cin>>psize;
		while(psize<50)
		{
			cout<<"\nInvalid entry. Enter size greater than or equal to 50 Square Guz: ";
			cin>>psize;
		}
		if(psize>=3000)
		{
			cout<<"\n\nLuxury Charge of 80000 Rs added.\n\n";
			baserate+=80000;
		}
		
		cout<<"\nEnter Base Rate in Rupees: ";
		cin>>baserate;
		while(baserate<=0)
		{
			cout<<"\nInvalid entry. Enter a valid base rate for property: ";
			cin>>baserate;
		}
		
		
		
		cout<<"\nEnter Property Popularity (H, High; L, Low): ";
		cin>>popularity;
		while(tolower(popularity)!='l' && tolower(popularity)!='h')
		{
			cout<<"\nInvalid entry. Enter Valid Property Popularity (H, High; L, Low): ";
			cin>>popularity;
		}
		
		popularity=tolower(popularity);
		if(tolower(popularity)=='h')
		servicefee=1.2;
		else
		servicefee=1.05;
		
		cout<<"\nBase rate adjusted for service fee:\n\tFee: Rs. "<<baserate*(servicefee-1)<<"Rs. \n\n";
		baserate=baserate*servicefee;
		
		while(1)
		{
			cout<<"\nIs the property roadfacing? Y/N: ";
			cin>>roadfacing;
			if(tolower(roadfacing)=='y' || tolower(roadfacing)=='n')
			{
				if(tolower(roadfacing)=='y')
				{
				baserate=baserate*(1.15);
				cout<<"\nBase Rate adjusted by 15% for road facing charges!\n";
				}
				break;
			}
			else
			cout<<"\nInvalid entry. ";	
		}
		
		cout<<"\nPlease enter purchase type (b for buy, r for rent): ";
		cin>>purchasetype;
		while(tolower(purchasetype)!='b' && tolower(purchasetype)!='r')
		{
			cout<<"\nInvalid entry. Please enter valid type: ";
			cin>>purchasetype;
		}
		if(tolower(purchasetype)=='r')
		{
			cout<<"\nEnter monthly rent for property (between Rs. 10000 & Rs. 1000000): ";
			cin>>monthrent;
			while(monthrent<10000 || monthrent>1000000)
			{
				cout<<"\nInvalid amount entered! Enter an amount between Rs. 10000 & Rs. 1000000: ";
				cin>>monthrent;
			}
		}
		
		fflush(stdin);
		cout<<"\n\nProperty Address:\n";
		cout<<"\nEnter City: ";
		cin.getline(paddress.city,50);
		cout<<"\nEnter Area: ";
		cin.getline(paddress.area,50);
		cout<<"\nEnter Block No. : ";
		cin.getline(paddress.block,50);
		cout<<"\nEnter Street: ";
		cin.getline(paddress.street,50);
		cout<<"\nEnter ZIP code: ";
		cin.getline(paddress.zip,50);
		
		cout<<"\nPlease enter date of construction of the property (Format:day month year) : ";
		cin>>constructiondate.d>>constructiondate.m>>constructiondate.y;
		while(constructiondate.d<=0 || constructiondate.m<=0 || constructiondate.y<1900)
		{
			cout<<"\nInvalid Date. Please enter valid date of construction of the property (Format:day month year) : ";
			cin>>constructiondate.d>>constructiondate.m>>constructiondate.y;
		}
		
		cout<<"\nIs the construction of old or new type? Enter O for Old, N for New: ";
		cin>>constype;
		while(tolower(constype)!='o' && tolower(constype)!='n')
		{
			cout<<"\nInvalid entry. Is the construction of old or new type? Enter O for Old, N for New: ";
			cin>>constype;
		}
		if(tolower(constype)=='n')
		{
			baserate*=1.1;
			cout<<"\nBase Rate adjusted by 10% for new construction charges!\n";
		}
		
	}
	
};	

//inherits from class property
//additional attrributes 
class residential: public property{
	protected:
	int rooms;
	int balcony;
	int orientation;
	int furnished;
	float furnishcost;
	float furnishcharge;
	public:
	residential(): property()
	{
		furnishcost=0;
		rooms=0;
		balcony=0;
		orientation=0;
		furnished=0;
		furnishcharge=0;
	}
	~residential()
	{
		
	}
	//overriden display function to extend base class displaydetails() function 
	void displaydetails() const
	{
		property::displaydetails();
		Sleep(300);
		cout<<"\nRooms: "<<rooms<<"\n";
		if(balcony==1)
		cout<<"\nBalcony: Yes";
		else
		cout<<"\nBalcony: No";
		cout<<"\n\nOrientation: ";
		if(orientation==1)
		cout<<"West Open\n";
		else if(orientation==2)
		cout<<"East Open\n";
		else if(orientation==3)
		cout<<"Other\n";
		Sleep(300);
		if(furnished==1)
		{
			cout<<"\nFurnished: Yes";
			cout<<"\nFurnish Cost: Rs. "<<furnishcost<<endl;
		}
		else
		{
			cout<<"\nFurnished: No";
			cout<<"\nFurnish Charges: Rs. "<<furnishcharge<<endl;
		}
		
		
	}
	//overrriden input details function to extend input
	void inputdetails()
	{
		property::inputdetails();
		cout<<"\nResidential Details:\n";
		cout<<"\n*Every room above 2 costs 100000 Rs.\nEnter Number of rooms: ";
		cin>>rooms;
		while(1)
		{
			if(rooms<=0)
			{
				cout<<"\nInvalid number entered. Enter 1 or more rooms: ";
				cin>>rooms;
			}
			else
			break;
		}
		
		if(rooms>2)
		{
			baserate=baserate+(rooms*100000);
			cout<<"\nBase rate updated.\n";
		}
		
		cout<<"\nDoes property have balcony? Enter 1 if so, or 2 if not: ";
		cin>>balcony;
		while(balcony!=1 && balcony!=2)
		{
			cout<<"\nIncorrect entry!\nDoes property have balcony? Enter 1 if so, or 2 if not: ";
			cin>>balcony;
		}
		if(balcony==1)
		{
			baserate+=140000;
			cout<<"\nRs. 140000 added for balcony.\n";
		}
	
		cout<<"\n\nChoose an orientation: 1.West Open\n2.East Open\n3. Other\n";
		cin>>orientation;
		while(orientation!=1 && orientation!=2 && orientation!=3)
		{
			cout<<"\nEnter valid choice: ";
			cin>>orientation;
		}
		
		switch (orientation)
		{
			case 1:
				baserate+=80000;
				break;
			case 2:
				baserate+=40000;
				break;
			default:
				break;
		}
		cout<<"\nBase rate adjusted!\n\n";
		
		
		cout<<"\n\nIs your property furnished? Enter 1 if so, or 2 if not: ";
		cin>>furnished;
		while(furnished!=1 && furnished!=2)
		{
			cout<<"\nEnter valid choice: ";
			cin>>furnished;
		}
		
		if(furnished==2)
		{
			cout<<"\n\nEnter a furnish charge (Rs.): ";
			cin>>furnishcharge;
			while(furnishcharge<=0)
			{
				cout<<"\nInvalid entry. Enter a furnish charge greater than zero: ";
				cin>>furnishcharge;
			}
		}
		else
		{
				cout<<"\n\nEnter a furnish cost: ";
				cin>>furnishcost;
				while(furnishcost<=0)
				{
					cout<<"\nInvalid entry. Enter a valid furnish cost: ";
					cin>>furnishcost;
				}
				while(furnishcost<(rooms*50000))
				{
					cout<<"\nFurnish cost can not be less than room cost! Room cost: Rs. "<<(rooms*50000)<<". Please enter at least that amount: ";
					cin>>furnishcost;
				}
				baserate+=furnishcost;
				cout<<"\nBase Rate updated with furnish cost.\n\n";
		}
	}
	
	int get_rooms()
	{
		return rooms;
	}
	int get_balcony()
	{
		return balcony;
	}
	int get_orientation()
	{
		return orientation;
	}
	int get_furnished()
	{
		return furnished;
	}
	float get_furnishcost()
	{
		return furnishcost;
	}
	
	void set_rooms(int r)
	{
		rooms=r;
	}
	void set_balcony(int b)
	{
		balcony=b;
	}
	void set_orientation(int o)
	{
		orientation=o;
	}
	void set_furnished(int f)
	{
		furnished=f;
	}
	void set_furnishcost(float fc)
	{
		furnishcost=fc;
	}
};
//inherits from class residential
//overrides input and display functions 
class house: public residential{
	int hno;
	char housetype[100];//villa,portion,
	int floors;
	public:
	house(): residential()
	{
		hno=1;
		floors=1;
	}
	~house()
	{
	}
	
	friend class customer;//friend classes to access property attributes directly due to has-a relationship
	friend class agent;
	friend class admin;
	friend int ViewProperties();
	//friend class guest; can not allow guest to access property details
	
	//overriden display function to extend base class displaydetails() function
	void displaydetails() const
	{
		residential::displaydetails();
		Sleep(300);
		cout<<"\nHouse No.: "<<hno<<"\nHouse Type: "<<housetype<<"\nNumber of floors: "<<floors<<endl;
	}
	//overriden input function to extend base class inputdetails() function
	void inputdetails()
	{
		residential::inputdetails();
		cout<<"\nHouse details: \n";
		proptype=1;
		cout<<"\nEnter House Number: ";
		cin>>hno;
		while(hno<=0)
		{
			cout<<"\nInvalid entry. Enter Valid House Number: ";
			cin>>hno;
		}
		int anch;
		cout<<"\nHouse Types:\n1. Villa\n2. Portion\n3. Penthouse\n\nEnter your choice:  ";
		cin>>anch;
		
		while(anch!=1 && anch!=2 && anch!=3)
		{
			cout<<"\nEnter valid option: ";
			cin>>anch;
		}
		
		if(anch==1)
		strcpy(housetype,"Villa");
		else if(anch==2)
		strcpy(housetype,"Portion");
		else
		strcpy(housetype,"Penthouse");
		
		fflush(stdin);
		/*cin.getline(housetype,100);*/
		
		cout<<"\n\nEnter Number of Floors in Residence:\n\n*No charges for upto 3 floors\n*Rs. 70000 per floor for floors betweeen 4 and 6\n*Rs. 95000 per floor for floors more than 6\n\nEnter number of floors: ";
		cin>>floors;
		while(floors<=0)
		{
			cout<<"\nInvalid entry. Enter Valid Number of Floors in Residence: ";
			cin>>floors;
		}
		
		if(floors>3 && floors<6)
		{
			baserate+=((floors-3)*70000);
			cout<<"\nBase rate adjusted for 70000 Rs. per floor.\n";
		}
		else if(floors>6)
		{
			baserate+=((floors-3)*95000);
			cout<<"\nBase rate adjusted for 95000 Rs. per floor above 3 floors.\n";
		}
		Sleep(200);
		cout<<"\n\nNow displaying tax information: ";
		Sleep(300);
		if(baserate<=1000000)
		{
		tax=baserate*0.15;
		printf("\nTax applicable on property: 15%, or Rs. %.2f",tax);
		}
		else if(baserate<=5000000)
		{
		tax=baserate*0.3;
		printf("\nTax applicable on property: 30%, or Rs. %.2f",tax);
		}
		else
		{
		tax=baserate*0.45;
		//cout<<"\nTax applicable on property: 45%, or Rs."<<tax;
		printf("\nTax applicable on property: 45%, or Rs. %.2f",tax);
		}
	}
	
	int get_hno()
	{
		return hno;
	}
	char* get_housetype()
	{
		return housetype;
	}
	int get_floors()
	{
		return floors;
	}
	void set_hno(int hn)
	{
		hno=hn;
	}
	void set_housetype(char *ht)
	{
		strcpy(housetype,ht);
	}
	void set_floors(int f)
	{
		floors=f;
	}
	
};
//inherits from residential class
//overrides input and display functions
class flat: public residential{
	int flatno;
	int  elevator;
	int parking;
	char complexname[50];
	int floorno;//price increases with elevation
	public:
	flat(): residential()
	{
		flatno=0;
		floorno=0;
		parking=0;
		elevator=0;
	}
	~flat()
	{
		
	}
	friend class customer;//see house class for explanation
	friend class agent;
	friend class admin;
	friend int ViewProperties();
	//friend class guest;
	//explained in house class
	void displaydetails() const
	{
		residential::displaydetails();
		Sleep(300);
		cout<<"\nFlat details:\n\n";
		Sleep(300);
		cout<<"\nFlat Number: "<<flatno<<"\nFloor Number: "<<floorno<<"\nComplex Name: "<<complexname<<endl;
		Sleep(300);
		if(elevator==1)
		cout<<"Elevator facility: Yes";
		else
		cout<<"Elevator facility: No";
		Sleep(300);
		if(parking==1)
		cout<<"\nParking facility: Yes";
		else
		cout<<"\nParking facility: No";
	}
	//explained in house class
	void inputdetails()
	{
		residential::inputdetails();
		cout<<"\nFlat details:\n\n";	
		proptype=2;
		cout<<"\nEnter Flat No. :";
		cin>>flatno;
			while(flatno<=0)
		{
			cout<<"\nInvalid entry. Enter Valid Flat Number: ";
			cin>>flatno;
		}
	
		cout<<"\n\n*Parking charges: Rs. 50000.\n Enter 1 if parking available, else 2:";
		cin>>parking;
			while(parking!=1 && parking!=2)
		{
			cout<<"\nInvalid entry. Enter Valid Choice: ";
			cin>>parking;
		}
		if(parking==1)
		{
			baserate+=50000;
		}
		cout<<"\n\n*Elevator service charges: Rs. 30000.\nEnter 1 for elevator service, else 2:";
		cin>>elevator;
			while(elevator!=1 && elevator!=2)
		{
			cout<<"\nInvalid entry. Enter Valid Choice: ";
			cin>>elevator;
		}
		if(elevator==1)
		{
			baserate+=30000;
		}
		cout<<"\nEnter complex name: ";
		fflush(stdin);
		cin.getline(complexname,50);
		
		cout<<"\nEnter floor number where flat is located: ";
		cin>>floorno;
		while(floorno<=0)
		{
			cout<<"\nInvalid entry. Enter Valid Floor Number (>0): ";
			cin>>floorno;
		}
		if(floorno>2)
		{
			baserate+=((floorno-2)*10000);
			cout<<"\nAdditional charges for 3rd floor and above: Rs "<<(floorno-2)*10000<<". Base rate updated!\n";
		}
		cout<<"\nNow displaying tax information: \n";
		//tax calculation
		if(baserate<=1000000)
		{
		tax=baserate*0.15;
		printf("\nTax applicable on property: 15%, or Rs. %.2f",tax);
		}
		else if(baserate<=5000000)
		{
		tax=baserate*0.3;
		printf("\nTax applicable on property: 30%, or Rs. %.2f",tax);
		}
		else
		{
		tax=baserate*0.45;
		printf("\nTax applicable on property: 45%, or Rs. %.2f",tax);
		}
		
	}
	//setters+getters
	int get_flatno()
	{
		return flatno;
	}
	int get_elevator()
	{
		return elevator;
	}
	int get_parking()
	{
		return parking;
	}
	char* get_complexname()
	{
		return complexname;
	}
	int get_floorno()
	{
		return floorno;
	}
	
	void set_flatno(int fn)
	{
		flatno=fn;
	}
	void set_elevator(int ev)
	{
		 elevator=ev;
	}
	void set_parking(int pk)
	{
		parking=pk;
	}
	void set_complexname(char *cn)
	{
		strcpy(complexname,cn);
	}
	void set_floorno(int fn)
	{
		floorno=fn;
	}
};

//composed within commercial class 
//commercial property has-a shop 
class Shops{
	int shopno;
	int nshops;
	char shoplocation;//internal,external
	char businesstype[150];//description of business
	public:
	Shops()
	{
		shopno=0;
		nshops=0;
		shoplocation='i';
	}
	friend class commercial;
	//to access shops attributes directly 
};



//inherits from property base class
//overrides input and display functions
class commercial: public property{
	Shops sho1;
	char zonename[50];
	public:
	commercial(): property()
	{
	}
	~commercial()
	{
	}
	friend class customer;//see residential class for explanation
	friend class agent;
	friend class admin;
	friend int ViewProperties();
	//friend class guest;
	//extends base display function by overriding 
	void displaydetails() const
	{
		property::displaydetails();
		Sleep(300);
		cout<<"\nShop No.: "<<sho1.shopno<<"\nNumber of Shops: "<<sho1.nshops<<"\nZone Name: "<<zonename<<endl;
		Sleep(150);
		cout<<"\nBusiness type: "<<sho1.businesstype;
		Sleep(200);
		if(tolower(sho1.shoplocation)=='e')
		cout<<"\nFront Facing\n";
		else
		cout<<"\nInternally located\n";
		
	}
	//extends base input function by overriding 
	void inputdetails()
	{
		property::inputdetails();
		cout<<"\nCommercial details: \n\n";
		proptype=3;
		cout<<"\nEnter shop number: ";
		cin>>sho1.shopno;
		while(sho1.shopno<=0)
		{
			cout<<"\nInvalid entry. Enter Valid Shop Number: ";
			cin>>sho1.shopno;
		}
		cout<<"\nRs. 60000 per shop added for shops more than 2.\nEnter number of shops:";
		cin>>sho1.nshops;
		while(sho1.nshops<=0)
		{
			cout<<"\nInvalid entry. Enter Valid Number of Shops : ";
			cin>>sho1.nshops;
		}
		if(sho1.nshops>=2)
		{
			baserate+=60000;
		}
		cout<<"\nBase Rate updated!\n";
		
		fflush(stdin);
		cout<<"\nEnter business type/description: ";
		cin.getline(sho1.businesstype,150);
		
		cout<<"\nEnter name of commercial zone: ";
		fflush(stdin);
		cin.getline(zonename,50);
		
		cout<<"\nIs the shop front-facing or internal?\n\n**Per Shop:\n*Front Facing charges: Rs. 120000\n*Internal charges: Rs. 40000\n\nEnter (I, internal; E, external): ";
		cin>>sho1.shoplocation;
		while(tolower(sho1.shoplocation)!='i' && tolower(sho1.shoplocation)!='e')
		{
			cout<<"\nInvalid entry. Enter Valid Location: ";
			cin>>sho1.shoplocation;
		}
		if(tolower(sho1.shoplocation)=='e')
		{
			baserate+=(120000*sho1.nshops);
		}
		else
		{
			baserate+=(sho1.nshops*40000);
		}
		cout<<"\nNow displaying tax information: \n";
		Sleep(300);
		//tax calculation
		if(baserate<=1000000)
		{
		tax=baserate*0.15;
		printf("\nTax applicable on property: 15%, or Rs. %.2f",tax);
		}
		else if(baserate<=5000000)
		{
		tax=baserate*0.3;
		printf("\nTax applicable on property: 30%, or Rs. %.2f",tax);
		}
		else
		{
		tax=baserate*0.45;
		printf("\nTax applicable on property: 45%, or Rs. %.2f",tax);
		}
	}
	

	
	//setters+getters
	int get_shopno()
	{
		return sho1.shopno;
	}
	int get_shops()
	{
		return sho1.nshops;
	}
	char get_shoplocation()
	{
		return sho1.shoplocation;
	}
	char* get_zonename()
	{
		return zonename;
	}
	void set_shopno(int bn)
	{
		sho1.shopno=bn;
	}
	void set_shops(int sh)
	{
		sho1.nshops=sh;
	}
	void set_shoplocation(char s)
	{
		sho1.shoplocation=s;
	}
	void set_zonename(char *zn)
	{
		strcpy(zonename,zn);
	}
};

//overloaded insertion operators for entering property details
istream & operator >>(istream &in,commercial &obj1)
{
	obj1.inputdetails();
	return in;
}

istream & operator >>(istream &in,house &obj2)
{
	obj2.inputdetails();
	return in;
}

istream & operator >>(istream &in,flat &obj3)
{
	obj3.inputdetails();
	return in;
}

ostream & operator <<(ostream &out,const commercial &obj1)
{
	obj1.displaydetails();
	return out;
}

ostream & operator <<(ostream &out,const house &obj1)
{
	obj1.displaydetails();
	return out;
}

ostream & operator <<(ostream &out,const flat &obj1)
{
	obj1.displaydetails();
	return out;
}

//base class of USER hierarchy
class user{
	protected:
	char uname[50],upass[50],useremail[50];
	char contactno[50];
	char fullname[50];
	public:
		user()
		{
			
		}
		/*user(char *u1,char *u2,char *u3, char *u4,char *u5)
		{
			strcpy(uname,u1);
			strcpy(upass,u2);
			strcpy(useremail,u3);
			strcpy(contactno,u4);
			strcpy(fullname,u5);
		}*/
		
		/*void inputdetails()
		{
			cout<<"\nEnter a unique username: ";
			getline(cin,uname);
			cout<<"\nEnter a unique password: ";
			getline(cin,upass);
			cout<<"\nEnter your email: ";
			getline(cin,useremail);
		}*/
		
		
		//setters, getters
		void set_uname(char *u1)
		{
			strcpy(uname,u1);
		}
		char* get_uname()
		{
			return uname;
		}
		
		void set_upass(char *u3)
		{
			strcpy(upass,u3);
		}
		char* get_upass()
		{
			return upass;
		}
		
		void set_useremail(char *u4)
		{
			strcpy(useremail,u4);
		}
		char* get_useremail()
		{
			return useremail;
		}
		
		void set_contactno(char *u5)
		{
			strcpy(contactno,u5);
		}
		char* get_contactno()
		{
			return contactno;
		}
		
		void set_fullname(char *u5)
		{
			strcpy(fullname,u5);
		}
		char* get_fullname()
		{
			return fullname;
		}
		//function to display basic user details
		void display1()
		{
			cout<<"\nName: "<<fullname<<"\nUsername: "<<uname<<"\nUser Password: "<<upass<<"\nUser Email: "<<useremail<<"\nContact number: "<<contactno;
		}
		//pure virtual functions for agent, customer and guest
		virtual void Menu1()=0;
		virtual void Menu2()=0;
		virtual void Logout()=0;
		
};

class customer;//forward declaration since some agent class member functions are COMPOSED of customer class objects 

//global function to validate contactno
int checknum(char* str1)
{
	int size=0,f1=0;
	for(int i=0;str1[i]!='\0';i++)
	{
		size++;
	}
	if(size!=11)
	return 0;
	else
	{
		for(int i=0;str1[i]!='\0';i++)
		{
			if(str1[i]>='0' && str1[i]<='9')
			f1=1;
			else
			{
			f1=0;
			break;
			}
		}
		if(f1==0)
		return 0;
		else
		return 1;
	}
}

//global function to validate email
int checkemail(char* str)
{
	int f1=0,f2=0,p1,p2;
	for(int i=0;str[i]!='\0';i++)
	{
		if(f1==0)
		{	
			if(str[i]=='@')
			{	
				f1=1;
				p1=i;
			}
			else
			f1=0;
		}
		if(f2==0)
		{
			if(p1!=0 && p1<i)
			{
				if(str[i]=='.')
				{
					f2=1;
					p2=i;
				}
				else
				f2=0;
			}
		}
	}
	int f3=0,count=0;
	if(p1<p2)
	f3=1;
	for(int i=0;str[i]!='\0';i++)
	{
		if(i>p1 && i<p2)
		count++;
	}
	if(f1==1 && f2==1 && f3==1 && count!=0)
	return 1;
	else
	return 0;
}


//publically inherited agent class
//lists both buy and lease type properties
//can manage and view sold+unsold props
//can collect rent from properties where applicable
//read+write access
class agent: public user{
	float crate;
	int agentid;
	char companyname[50];
	int totalsales;
	float rentcollected;
	float income;
	char description[150];
	
	public:
		agent(): user() 
		{
			totalsales=0;
			rentcollected=0;
			income=0;
			crate=0;	
		}
		~agent()
		{
		}
		//admin and customer must have access to agent attributes
		friend class customer;
		friend class admin;
		
		//Login/Registration portal that redirects to Account Portal 
		void Menu1()
		{
			int mech;
			while(1)//loop to ensure correct entry and iteration
			{
			system("cls");
			cout<<"\n********************AGENT PORTAL********************\n\n";
			cout<<"\n1. Register\n2. Login\n3. Exit\nEnter your choice: ";
			cin>>mech;
			while(mech<1 || mech>3)
			{
				cout<<"\nInvalid entry. Enter valid choice: ";
				cin>>mech;
			}
			if(mech==1)
			{
				Register();
			}
			else if(mech==2)
			{
				if(Login()==1)
				Menu2();//only call account portal iff login was successful i.e returned 1
				break;
			}
			else
			{
			cout<<"\nNow exiting\n";
			break;
			}
			}
		}
		
		//2nd Menu to access user account portal
		void Menu2()
		{
			int mech,imech;
			cout<<"\n********************AGENT PORTAL********************\n\n";
			while(1)
			{
				system("cls");
				cout<<"\n\n1. View Available Properties\n2. List a property\n3. Manage Your Properties\n4. View account information\n5. Logout\n\nEnter a choice: ";
				cin>>mech;	
				while(mech<1 && mech>5)
				{
					cout<<"\nInvalid entry. Enter valid choice: ";
					cin>>mech;	
				}
				
				if(mech==1)
				{
					ViewProperties();
				}
				else if(mech==2)
				{
					list_property();
				}
				else if(mech==3)
				{
					view_sold_properties();
				}
				else if(mech==4)
				{
					view_accountdetails();
				}
				else if(mech==5)
				{
					Logout();
					break;
				}
				
			}
		}
		
		//logout function
		void Logout()
		{
			time_t now = time(0);
   char* date_time = ctime(&now);
   cout <<"\n\nNow logging out Agent  "<<this->fullname<<"\n\nTime of exit: "<< date_time << endl;
	cout<<"\n\n\n";
	cout<<"\n*******************************THANK YOU FOR USING OUR SYSTEM*******************************";
	Sleep(400);
		}
		
		//setters + getters
		float get_crate()
		{
			return crate;
		}
		void set_crate(float n1)
		{
			crate=n1;
		}
		
		char* get_companyname()
		{
			return companyname;
		}
		void set_companyname(char *str2)
		{
			strcpy(companyname,str2);
		}
		
		char* get_description()
		{
			return description;
		}
		void set_description(char *str2)
		{
			strcpy(description,str2);
		}
		
		float get_income()
		{
			return income;
		}
		int get_totalsales()
		{
			return totalsales;
		}
		
		float get_rentcollected()
		{
			return rentcollected;
		}
		int get_agentid()
		{
			return agentid;
		}
		void set_agentid(int val)
		{
			agentid=val;
		}
		
		//register for a new user account, checks for existing usernames
		//signup
		void Register()
	{
		cout<<"\n\n\t\t************AGENT PORTAL************\n\t***REGISTRATION***\n\n\n";
		int index=0;
		char c;
		agent a1,a2;
		string filename="AgentInfo.dat";
		fflush(stdin);
		cout<<"\nEnter a unique username: ";
		cin.getline(uname,50);
		
		fstream cptr(filename.c_str(),ios::in|ios::app|ios::binary);
		if(!cptr)
		{
			cout<<"\nError opening file.\n";
			exit(1);
		}
		cptr.seekg(0,ios::end);
		if(cptr.tellg()==0)
		{
			a1.set_uname(uname);
		
			fflush(stdin);
			cout<<"\nEnter a unique password: ";
  			cin.getline(this->upass,50);
  			while(checkpass(this->upass)!=1)
			{
				cout<<"\nInvalid password entered! Password must:\n\t*Be at least 8 characters long\n\t*Have at least 1 capital letter\n\nEnter password: ";
				cin.getline(this->upass,50);
			}
			a1.set_upass(upass);
			fflush(stdin);
			cout<<"\nEnter you full name: ";
			cin.getline(fullname,50);
			a1.set_fullname(fullname);
			
			cout<<"\nEnter your email: ";
			fflush(stdin);
			cin.getline(useremail,50);
			while(checkemail(useremail)!=1)
			{
				cout<<"\nInvalid address. Enter valid email address: ";
				cin.getline(useremail,50);
			}
			a1.set_useremail(useremail);
		
			cout<<"\nEnter your contact number: ";
			fflush(stdin);
			cin.getline(contactno,50);
			while(checknum(contactno)!=1)
			{
				cout<<"\nInvalid number. Enter valid number: ";
				cin.getline(contactno,50);
			}
			a1.set_contactno(contactno);
			a1.set_agentid(50000);
			
			fflush(stdin);
			cout<<"\nEnter your agency company's name: ";
			cin.getline(companyname,50);
			a1.set_companyname(companyname);
			cout<<"\nEnter agent description (to be displayed for customers): ";
			cin.getline(description,150);
			a1.set_description(description);
			
			cout<<"\nEnter a commision rate (between 5 and 20 %): ";
			while(1)
			{
				cin>>crate;
				if(crate<5 || crate>20)
				{
					cout<<"\nInvalid rate entered! Enter a value between 5 and 20 (%): ";
					//cin>>crate;
				}
				else
				break;
			}
			a1.set_crate(crate);
			
			cptr.seekp(0,ios::beg);
			cptr.write((char*)&a1,sizeof(agent));
			cout<<"\nAccount successfully created!\n";
			cptr.close();
		}
		else 
		{
				cptr.close();
				cptr.open(filename.c_str(),ios::in|ios::out|ios::binary);
				int flag;
				while(1)
				{
					flag=0;
					cptr.clear();
					cptr.seekg(0,ios::beg);
					cptr.read((char*)&a2,sizeof(agent));
					while(!cptr.eof())
					{
						if(strcmp(a2.get_uname(),uname)==0)
						{
							flag=1;
							break;
						}
						cptr.read((char*)&a2,sizeof(agent));
					}
					if(flag==1)
					{
						fflush(stdin);
						cout<<"\nUsername already exists. Enter a new username: ";
						cin.getline(uname,50);
					}
					else if(flag==0)
					{
						break;
					}
				}
				
				cptr.clear();
				cptr.seekg(-(sizeof(agent)),ios::end);
				cptr.read((char*)&a2,sizeof(agent));
				
				a1.set_agentid( (a2.get_agentid())+1 );
				a1.set_uname(uname);
				
				fflush(stdin);
			cout<<"\nEnter a unique password: ";
  			cin.getline(this->upass,50);
  			while(checkpass(this->upass)!=1)
			{
				cout<<"\nInvalid password entered! Password must:\n\t*Be at least 8 characters long\n\t*Have at least 1 capital letter\n\nEnter password: ";
				cin.getline(this->upass,50);
			}
				a1.set_upass(upass);
				
				fflush(stdin);
				cout<<"\nEnter you full name (No more than 50 characters): ";
				cin.getline(fullname,50);
				a1.set_fullname(fullname);
				fflush(stdin);
				cout<<"\nEnter your email (No more than 50 characters): ";
				fflush(stdin);
				cin.getline(useremail,50);
				while(checkemail(useremail)!=1)
				{
					cout<<"\nInvalid address. Enter valid email address: ";
					cin.getline(useremail,50);
				}
				a1.set_useremail(useremail); 
				fflush(stdin);	
				cout<<"\nEnter your contact number: ";
				fflush(stdin);
				cin.getline(contactno,50);
				while(checknum(contactno)!=1)
				{
					cout<<"\nInvalid number. Enter valid number: ";
					cin.getline(contactno,50);
				}
				a1.set_contactno(contactno);
				
				fflush(stdin);
				cout<<"\nEnter your agency company's name: ";
				cin.getline(companyname,50);
				a1.set_companyname(companyname);
				cout<<"\nEnter agent description (to be displayed for customers): ";
				cin.getline(description,150);
				a1.set_description(description);
			
				cout<<"\nEnter a commision rate (between 5 and 20 %): ";
				while(1)
				{
					cin>>crate;
					if(crate<5 || crate>20)
					{
						cout<<"\nInvalid rate entered! Enter a value between 5 and 20 (%)";
						//cin>>crate;
					}
					else
					break;
				}
				a1.set_crate(crate);
				
				cptr.clear();
				cptr.seekp(0,ios::end);
				cptr.write((char*)&a1,sizeof(agent));
				cout<<"\nAccount successfully created!\n";
				cptr.close();
		}
			
	}
	//allows user to log in to their account
	//checks for both usernames and their associated passwords
	int Login()
	{
		int rchoice;
		agent a3;
		int anbh;
		cout<<"\n\t***AGENT LOGIN***\n\n\n";
		
		string filename="AgentInfo.dat";
		fflush(stdin);
		cout<<"\nEnter your username: ";
		cin>>uname;
		fstream cptr;
		cptr.open(filename.c_str(),ios::binary|ios::in|ios::out);
		if(!cptr)
		{
			cout<<"\nError opening file.\n\n";
			exit(1);
		}
		int flag;
		while(1)
		{
					flag=0;
					cptr.clear();
					cptr.seekg(0,ios::beg);
					cptr.read((char*)&a3,sizeof(agent));
					while(!cptr.eof())
					{
						if(strcmp(a3.get_uname(),uname)==0)
						{
							flag=1;
							break;
						}
						cptr.read((char*)&a3,sizeof(agent));
					}
					if(flag==1)
					{
						break;
					}
					else if(flag==0)
					{
						
						cout<<"\nUsername not found. Do you want to try again? Enter 1 to continue, else exit: ";
						cin>>anbh;
						if(anbh==1)
						{
							fflush(stdin);
							cout<<"\nEnter your existing username: ";
							cin.getline(uname,50);
						}
						else
						{
							cptr.close();
							return 0;	
						}
					
					}
		}
		cout<<"\n\nEnter your password: ";
		cin>>upass;
		while(1)
		{
					flag=0;
					cptr.clear();
					cptr.seekg(0,ios::beg);
					cptr.read((char*)&a3,sizeof(agent));
					while(!cptr.eof())
					{
						if(strcmp(a3.get_upass(),upass)==0)
						{
							flag=1;
							break;
						}
						cptr.read((char*)&a3,sizeof(agent));
					}
					if(flag==1)
					{
						cout<<"\n\tYou are now logged in!\n"<<"\n\tWelcome back, "<<a3.get_fullname()<<endl<<endl;
						copyobj(a3);
						Sleep(400);
						cptr.close();
						return 1;
						break;
					}
					else if(flag==0)
					{
						fflush(stdin);
						while(1)
						{
							cout<<"\nIncorrect password. Enter 1 to try again, or any other key to exit: ";
							cin>>rchoice;
							if(rchoice==1)
							{
								cout<<"\nEnter correct password: ";
								cin>>upass;
								break;
							}
							else
							{
								//return 0;
								break;
							}
						}
						if(rchoice!=1)
						{
							cout<<"\nExiting...";
							cptr.close();
							return 0;
							break;
							
						}
					}
		}
		cptr.close();	
		
	}
	//copy stored object attributes to *this upon logging in 
	void copyobj(agent c3)
	{
		strcpy(useremail,c3.get_useremail());
		strcpy(contactno,c3.get_contactno());
		agentid=c3.get_agentid();
		strcpy(fullname,c3.get_fullname());
		strcpy(uname,c3.get_uname());
		strcpy(upass,c3.get_upass());
		totalsales=c3.get_totalsales();
		rentcollected=c3.get_rentcollected();
		income=c3.get_income();
		strcpy(description,c3.get_description());
		strcpy(companyname,c3.get_companyname());
		crate=c3.get_crate();
	}
	
	
		
	//rent collection functions	
	int collect_rent(flat rflat);
	int collect_rent(house rhouse);
	int collect_rent(commercial rcom);
	//void get_income();
	
	
	
	int view_sold_properties();
	
	//function to add a buyable or rentable property
	void list_property()
	{
		int achoice,ch1;
		cout<<"\nWhat type of property do you wish to list?\n\n1. Commercial\n2. Residential\n\nEnter your choice: ";
		cin>>achoice;
		while(achoice !=1 && achoice!=2)
		{
			cout<<"\nInvalid choice entered. Please enter 1 for commercial or 2 for residential: ";
			cin>>achoice;
		}
		if(achoice==2)
		{
			cout<<"\nRESIDENTIAL\n\n"<<"1. House\n2. Flat"<<"\n\nEnter your choice: ";
			cin>>ch1;
			while(ch1!=1 && ch1!=2)
			{
			cout<<"\nInvalid choice entered. Please enter 1 for House or 2 for Flat: ";
			cin>>ch1;
			}
			
			if(ch1==1)
			{
				house h1;
				cout<<"\n\n*****HOUSE DETAILS*****\n\n";
				cout<<"\nPlease enter ALL of the following details for the property...\n\n";
				//h1.inputdetails();//assign IDs
				cin>>h1;
				//IDs assigned from 9000 and onwards in steps of 1
				fstream fptr;
				string filename="House.dat";
				fptr.open(filename.c_str(),ios::binary|ios::in|ios::app);
				fptr.seekg(0,ios::end);
				if(fptr.tellg()==0)
				{
					h1.set_propertyid(9000);
					h1.set_sellerid(agentid);
					h1.set_ownerid(agentid);
					h1.set_sellername(fullname);
					h1.set_ownername(fullname);
					fptr.clear();
					fptr.write((char*)&h1,sizeof(house));
					cout<<"\n\nProperty successfully added!\nProperty ID: "<<h1.propertyid;
					cout<<"\nPress any key to continue...";
					getchar(); 
					getchar();
				}
				else
				{
					house h2;
					fptr.close();
					fptr.open(filename.c_str(),ios::binary|ios::in|ios::out);
					fptr.clear();
					fptr.seekg(-sizeof(house),ios::end);
					fptr.read((char*)&h2,sizeof(house));
					
					h1.set_propertyid(h2.propertyid+1);
					h1.set_sellerid(agentid);
					h1.set_ownerid(agentid);
					h1.set_sellername(fullname);
					h1.set_ownername(fullname);
					fptr.clear();
					fptr.seekp(0,ios::end);
					fptr.write((char*)&h1,sizeof(house));
					cout<<"\n\nProperty successfully added!\nProperty ID: "<<h1.propertyid;
					cout<<"\nPress any key to continue...";
					getchar(); 
					getchar();
				}
				fptr.close();
				//totalsales+=1;
			}
			else
			{
				flat f1;
				cout<<"\n\n*****FLAT DETAILS*****\n\n";
				cout<<"\nPlease enter ALL of the following details for the property...\n\n";
				//f1.inputdetails();//assign IDs
				cin>>f1;
				//IDs assigned from 6000 and onwards in steps of 1
				fstream fptr;
				string filename="Flats.dat";
				fptr.open(filename.c_str(),ios::binary|ios::in|ios::app);
				fptr.seekg(0,ios::end);
				if(fptr.tellg()==0)
				{
					f1.set_propertyid(6000);
					f1.set_sellerid(agentid);
					f1.set_ownerid(agentid);
					f1.set_sellername(fullname);
					f1.set_ownername(fullname);
					fptr.clear();
					fptr.write((char*)&f1,sizeof(flat));
					cout<<"\n\nProperty successfully added!\nProperty ID: "<<f1.propertyid;
					cout<<"\nPress any key to continue...";
					getchar(); 
					getchar();
				}
				else
				{
					flat f2;
					fptr.close();
					fptr.open(filename.c_str(),ios::binary|ios::in|ios::out);
					fptr.clear();
					fptr.seekg(-sizeof(flat),ios::end);
					fptr.read((char*)&f2,sizeof(flat));
					
					f1.set_propertyid(f2.propertyid+1);
					f1.set_sellerid(agentid);
					f1.set_ownerid(agentid);
					f1.set_sellername(fullname);
					f1.set_ownername(fullname);
					fptr.clear();
					fptr.seekp(0,ios::end);
					fptr.write((char*)&f1,sizeof(flat));
					cout<<"\n\nProperty successfully added!\nProperty ID: "<<f1.propertyid;
					cout<<"\nPress any key to continue...";
					getchar(); 
					getchar();
				}
				fptr.close();
				//totalsales+=1;
			}
		
		}
		else
		{
				commercial com1;
				cout<<"\n\n*****COMMERCIAL DETAILS*****\n\n";
				cout<<"\nPlease enter ALL of the following details for the property...\n\n";
				//com1.inputdetails();
				cin>>com1;
				//assign IDs
				//IDs assigned from 13000 and onwards in steps of 1
				fstream fptr;
				string filename="Commercial.dat";
				fptr.open(filename.c_str(),ios::binary|ios::in|ios::app);
				fptr.seekg(0,ios::end);
				if(fptr.tellg()==0)
				{
					com1.set_propertyid(13000);
					com1.set_sellerid(agentid);
					com1.set_ownerid(agentid);
					com1.set_sellername(fullname);
					com1.set_ownername(fullname);
					fptr.clear();
					fptr.write((char*)&com1,sizeof(commercial));
					cout<<"\n\nProperty successfully added!\nProperty ID: "<<com1.propertyid;
					cout<<"\nPress any key to continue...";
					getchar(); 
					getchar();
				}
				else
				{
					commercial com2;
					fptr.close();
					fptr.open(filename.c_str(),ios::binary|ios::in|ios::out);
					fptr.clear();
					fptr.seekg(-sizeof(commercial),ios::end);
					fptr.read((char*)&com2,sizeof(commercial));
					
					com1.set_propertyid(com2.propertyid+1);
					com1.set_sellerid(agentid);
					com1.set_ownerid(agentid);
					com1.set_sellername(fullname);
					com1.set_ownername(fullname);
					fptr.clear();
					fptr.seekp(0,ios::end);
					fptr.write((char*)&com1,sizeof(commercial));
					cout<<"\n\nProperty successfully added!\nProperty ID: "<<com1.propertyid;
					cout<<"\nPress any key to continue...";
					getchar(); 
					getchar();
				}
				fptr.close();
				//totalsales+=1;
		}
	//updating agent account
	/*agent ag1;
	fstream aptr;	
	string filename="AgentInfo.dat";
	aptr.open(filename.c_str(),ios::binary|ios::in|ios::out);
	aptr.read((char*)&ag1,sizeof(agent));
	while(!aptr.eof())
	{
		if((this->agentid)==ag1.agentid)
		{
			break;
		}
	}
	aptr.clear();
	aptr.seekp(-sizeof(agent),ios::cur);
	aptr.write(((char*)&(*this)),sizeof(agent));
	cout<<"\nTotal properties updated.\n";
	aptr.close();*/
	}
	
	
	//void generate_notifications();//create notification for customer
	//observe account information and optionally update your password	
	void view_accountdetails()
	{
		int ach;
		display1();
		cout<<"\n\nAccount Details:\nAgent ID: "<<agentid<<"\nAgent Description: \n"<<description<<"\n\nCommission Rate: "<<crate<<"%\nCompany Name:\n"<<companyname<<"\n\nTotal Sales: "<<totalsales<<"\nRent collected: "<<rentcollected<<"\nTotal income (from sales): "<<income;
		cout<<"\nDo you wish to update your password? Enter 1 for yes, or any other key for no: ";
		cin>>ach;
		if(ach==1)
		{
			agent ag1;
			fstream aptr;	
			string filename="AgentInfo.dat";
			aptr.open(filename.c_str(),ios::binary|ios::in|ios::out);
			aptr.read((char*)&ag1,sizeof(agent));
			while(!aptr.eof())
			{
				if((this->agentid)==ag1.agentid)
				{
					break;
				}
				aptr.read((char*)&ag1,sizeof(agent));
			}
			fflush(stdin);
			cout<<"\nEnter a unique password: ";
  			cin.getline(this->upass,50);
  			while(checkpass(this->upass)!=1)
			{
				cout<<"\nInvalid password entered! Password must:\n\t*Be at least 8 characters long\n\t*Have at least 1 capital letter\n\nEnter password: ";
				cin.getline(this->upass,50);
			}
			ag1.set_upass(upass);
			aptr.clear();
			aptr.seekp(-sizeof(agent),ios::cur);
			aptr.write((char*)&ag1,sizeof(agent));
			aptr.close();
			this->copyobj(ag1);
			cout<<"\nAccount password successfully updated!. Press any key to continue...";
			getchar();
			getchar();
			
		}
		else
		{
			cout<<"\nPassword unchanged.\n\nPress any key to continue...";
			getchar();
			getchar();
		}
		
	}
		
	
};
//publically inherited customer class
// can buy and rent properties
//can view contracts of owned properties
//option for rent to buy
//can create wishlists
//read+write access
class customer: public user{
	int custid;
	float acctotal;
	int totalprops;
	float buytotal,renttotal;
	float budget;//can be disabled, used to view property (-1 means disabled)
	
	public:
	customer(): user()
	{
		acctotal=0;
		totalprops=0;
		buytotal=0;
		renttotal=0;
		budget=-1;//budget disabled by default 
	}
	~customer()
	{
	}
	friend class agent;//authorizes agent and admin modules to update a customer object  
	friend class admin;
	
	void update_total(float val)
	{
		acctotal+=val;
	}
	//refer to agent function of same name(overriden from base class user)
	void Menu1()
	{
			int mech;
			cout<<"\n********************CUSTOMER PORTAL********************\n\n";
			while(1)
			{
			system("cls");
			cout<<"\n1. Register\n2. Login\n3. Exit\nEnter your choice: ";
			cin>>mech;
			while(mech<1 || mech>3)
			{
				cout<<"\nInvalid entry. Enter valid choice: ";
				cin>>mech;
			}
			
			if(mech==1)
			{
				Register();
			}
			else if(mech==2)
			{
				if(Login()==1)
				Menu2();
				break;
			}
			else
			{
				cout<<"\nNow exiting\n";
				break;	
			}
			
			}
	}
	//refer to agent function of same name(overriden form base class user)
	void Menu2()
	{
		int mech;
		int imech;
		cout<<"\n************************************CUSTOMER PORTAL************************************\n\n";
		while(1)
		{
			system("cls");
			cout<<"\n\n1. View Available Properties\n2. Buy And Rent\n3. Manage Your Properties\n4. Manage wishlist\n5. View Account Information\n6. Logout\n\nEnter your choice: ";
			cin>>mech;
			while(mech<1 || mech>6)
			{
				cout<<"\nInvalid entry. Enter correct choice: ";
				cin>>mech;
			}
	
			if(mech==1)
			{
				ViewProperties();
			}
			else if(mech==2)
			{
				this->buy_property();
			}
			else if(mech==3)
			{
				
				cout<<"\n1. Bought properties\n2. Rented properties\n\nEnter your choice: ";
				cin>>imech;
				if(imech==1)
				{
					this->view_bought();
				}
				else
				{
					this->view_rented();
				}
			}
			else if(mech==4)
			{
				cout<<"\nWishlist\n\n1. Add to wishlist\n2. View current wishlist\nEnter your choice: ";
				cin>>imech;
				if(imech==1)
				{
					this->update_wishlist();
				}
				else if(imech==2)
				{
					this->view_wishlist();
				}
			}
			else if(mech==5)
			{
				this->view_accountdetails();
			}
			else if(mech==6)
			{
				this->Logout();
				break;
			}
		}
	}
	
	void Logout()
	{
			time_t now = time(0);
   char* date_time = ctime(&now);
   Sleep(400);
   cout <<"\n\nNow logging out Customer  "<<this->fullname<<"  ID: "<<this->custid<<"\n\nTime of exit: "<< date_time << endl;
	cout<<"\n\n\n";
	cout<<"\n*******************************THANK YOU FOR USING OUR SYSTEM*******************************";
	Sleep(400);
	}
	
	//setters + getters
	float get_acctotal() const
	{
		return acctotal;
	}
	
	int get_tprops() const
	{
		return totalprops;
	}
	
	float get_buytotal() const
	{
		return buytotal;
	}
	
	float get_renttotal() const
	{
		return renttotal;
	}
	
	float get_budget() const
	{
		return budget;
	}
	
	void set_budget(float v1)
	{
		budget=v1;
	}
	void set_custid(int num)
	{
		custid=num;
	}
	
	int get_custid() const
	{
		return custid;
	}
	//signup
	//searches for existing usernames if any
	//prevents record duplication
	void Register()
	{
		int index=0;
		char c;
		customer c1,c2;
		fstream cptr;
		string filename="CustomerInfo.dat";
		fflush(stdin);
		cout<<"\nEnter a unique username: ";
		cin>>this->uname;
		cptr.open(filename.c_str(),ios::in|ios::app|ios::binary);
		cptr.seekg(0,ios::end);
		
		if(cptr.tellg()==0)
		{
			c1.set_uname(this->uname);
			fflush(stdin);
			cout<<"\nEnter a unique password: ";
  			cin.getline(this->upass,50);
  			while(checkpass(this->upass)!=1)
			{
				cout<<"\nInvalid password entered! Password must:\n\t*Be at least 8 characters long\n\t*Have at least 1 capital letter\n\nEnter password: ";
				cin.getline(this->upass,50);
			}
			c1.set_upass(this->upass);
			
			fflush(stdin);
			cout<<"\nEnter you full name: ";
			cin.getline(this->fullname,50);
			c1.set_fullname(this->fullname);
			
			cout<<"\nEnter your email: ";
			fflush(stdin);
			cin.getline(this->useremail,50);
			while(checkemail(this->useremail)!=1)
			{
				cout<<"\nInvalid address. Enter valid email address: ";
				cin.getline(this->useremail,50);
			}
			c1.set_useremail(this->useremail); 
		
			cout<<"\nEnter your contact number: ";
			fflush(stdin);
			cin.getline(this->contactno,50);
			while(checknum(this->contactno)!=1)
			{
				cout<<"\nInvalid number. Enter valid number: ";
				cin.getline(this->contactno,50);
			}
			c1.set_contactno(this->contactno);
			c1.set_custid(1100);
			cptr.seekp(0,ios::beg);
			cptr.write((char*)&c1,sizeof(customer));
			cout<<"\nAccount successfully created!\n";
			cptr.close();
		}
		else 
		{
				int flag;
				cptr.close();
				cptr.open(filename.c_str(),ios::in|ios::out|ios::binary);
				while(1)
				{
					flag=0;
					cptr.clear();
					cptr.seekg(0,ios::beg);
					cptr.read((char*)&c2,sizeof(customer));
					while(!cptr.eof())
					{
						if(strcmp(c2.get_uname(),uname)==0)
						{
							flag=1;
							break;
						}
						cptr.read((char*)&c2,sizeof(customer));
					}
					if(flag==1)
					{
						fflush(stdin);
						cout<<"\nUsername already exists. Enter a new username: ";
						cin.getline(uname,50);
					}
					else if(flag==0)
					{
						break;
					}
				}
				
				cptr.clear();
				cptr.seekg(-(sizeof(customer)),ios::end);
				cptr.read((char*)&c2,sizeof(customer));
				
				c1.set_custid( (c2.get_custid())+1 );
				c1.set_uname(uname);
				
				fflush(stdin);
			cout<<"\nEnter a unique password: ";
  			cin.getline(this->upass,50);
  			while(checkpass(this->upass)!=1)
			{
				cout<<"\nInvalid password entered! Password must:\n\t*Be at least 8 characters long\n\t*Have at least 1 capital letter\n\nEnter password: ";
				cin.getline(this->upass,50);
			}
				c1.set_upass(upass);
				
				fflush(stdin);
				cout<<"\nEnter you full name: ";
				cin.getline(fullname,50);
				c1.set_fullname(fullname);
				fflush(stdin);
				cout<<"\nEnter your email: ";
				fflush(stdin);
				cin.getline(this->useremail,50);
				while(checkemail(this->useremail)!=1)
				{
					cout<<"\nInvalid address. Enter valid email address: ";
					cin.getline(this->useremail,50);
				}
				c1.set_useremail(useremail); 
				fflush(stdin);	
				cout<<"\nEnter your contact number: ";
				fflush(stdin);
				cin.getline(this->contactno,50);
				while(checknum(this->contactno)!=1)
				{
					cout<<"\nInvalid number. Enter valid number: ";
					cin.getline(this->contactno,50);
				}
				c1.set_contactno(this->contactno);
				
				cptr.seekp(0,ios::end);
				cptr.write((char*)&c1,sizeof(customer));
				cout<<"\nAccount successfully created!\n";
				cptr.close();
		}
			
	}
	//logs the user in by authenticating first the username, then user password
	int Login()
	{
		int rchoice;
		customer c3;
		string filename="CustomerInfo.dat";
		fflush(stdin);
		cout<<"\nEnter your username: ";
		cin>>uname;
		fstream cptr;
		cptr.open(filename.c_str(),ios::binary|ios::in|ios::out);
		if(!cptr)
		{
			cout<<"\nError opening file\n\n";
			exit(1);
		}
		int flag;
		while(1)
		{
					flag=0;
					cptr.clear();
					cptr.seekg(0,ios::beg);
					cptr.read((char*)&c3,sizeof(customer));
					while(!cptr.eof())
					{
						if(strcmp(c3.get_uname(),uname)==0)
						{
							flag=1;
							break;
						}
						cptr.read((char*)&c3,sizeof(customer));
					}
					if(flag==1)
					{
						break;
					}
					else if(flag==0)
					{
						fflush(stdin);
						cout<<"\nUsername not found. Enter your existing username: ";
						cin.getline(uname,50);
					}
		}
		cout<<"\nEnter your password (Max length 50, no special characters): ";
		cin>>upass;
		while(1)
		{
					flag=0;
					cptr.clear();
					cptr.seekg(0,ios::beg);
					cptr.read((char*)&c3,sizeof(c3));
					while(!cptr.eof())
					{
						if(strcmp(c3.get_upass(),upass)==0)
						{
							flag=1;
							break;
						}
						cptr.read((char*)&c3,sizeof(c3));
					}
					if(flag==1)
					{
						cout<<"\nYou are now logged in!\n"<<"\nWelcome back, "<<c3.get_fullname()<<endl<<endl;;
						copyobj(c3);
						cptr.close();
						Sleep(400);
						return 1;
						break;
					}
					else if(flag==0)
					{
						fflush(stdin);
						while(1)
						{
							cout<<"\nEnter 1 to try again, or any other key to exit: ";
							cin>>rchoice;
							if(rchoice==1)
							{
								cout<<"\nEnter correct password: ";
								cin>>upass;
								break;
							}
							else
							{
								cout<<"\nExiting...";
								break;
							}
						}
						if(rchoice!=1)
						{
							cptr.close();
							return 0;
							break;
						}
					}
		}
		cptr.close();	
		
	}
	
	void copyobj(customer c3)
	{
		strcpy(useremail,c3.get_useremail());
		strcpy(contactno,c3.get_contactno());
		custid=c3.get_custid();
		strcpy(fullname,c3.get_fullname());
		strcpy(uname,c3.get_uname());
		strcpy(upass,c3.get_upass());
		acctotal=c3.get_acctotal();
		buytotal=c3.get_buytotal();
		renttotal=c3.get_renttotal();
		totalprops=c3.get_tprops();
		budget=c3.get_budget();
	}
	
	//view rented properties
	int view_rented()
	{
		int pchoice,cho1;
		fstream f1ptr,f2ptr,f3ptr;
		string str1="House.dat";
		string str2="Flats.dat";
		string str3="Commercial.dat";
		
		f1ptr.open(str1.c_str(),ios::binary|ios::in|ios::out);
		f2ptr.open(str2.c_str(),ios::binary|ios::in|ios::out);
		f3ptr.open(str3.c_str(),ios::binary|ios::in|ios::out);
		f1ptr.seekg(0,ios::end);
		f2ptr.seekg(0,ios::end);
		f3ptr.seekg(0,ios::end);
		
		if(f1ptr.tellg()==0 && f2ptr.tellg()==0 && f3ptr.tellg()==0)
		{
			cout<<"\nError. No records to display.\n\n";
		}
		
		f1ptr.seekg(0,ios::beg);
		f2ptr.seekg(0,ios::beg);
		f3ptr.seekg(0,ios::beg);
		int count=0;
		int p1;
		char sr1[20],sr2[20];
		cout<<"\n**********PROPERTIES**********\n\n\n";
		cout<<"******PROPERTY TYPE******\n\n1. RESIDENTIAL\n2. COMMERCIAL\nEnter your choice: ";
		cin>>pchoice;
		while(pchoice<1 || pchoice>2)
		{
				cout<<"\nInvalid entry! Enter valid choice: ";
				cin>>pchoice;
		}
		if(pchoice==2)
		{
			commercial cm1,cm2;
			f3ptr.clear();
			f3ptr.read((char*)&cm1,sizeof(commercial));
			while(!f3ptr.eof())
			{
				if(cm1.ownerid==(this->custid) && tolower(cm1.purchasetype)=='r')
				count++;
				f3ptr.read((char*)&cm1,sizeof(commercial));
			}
			if(count==0)
			{
				cout<<"\nNo commercial properties to display.\nPress any key to continue...";
				f3ptr.close();
				f2ptr.close();
				f1ptr.close();
				getchar();
				getchar();
				return 1;
				
			}
			else
			{
				int index=0;
				f3ptr.clear();
				f3ptr.seekg(0,ios::beg);
				commercial comarr[count];
				f3ptr.read((char*)&cm1,sizeof(commercial));
				
				cout<<"\nSerial No. | Name | Size | Available | Shops | Facing Type | Purchase Type | Commercial Zone | Buy Price (Rs.)\n";
				while(!f3ptr.eof())
				{
					if(cm1.ownerid==(this->custid) && tolower(cm1.purchasetype)=='r')
					{
					comarr[index]=cm1;
					index+=1;
					strcpy(sr1,"YES");
					
					if(cm1.get_shoplocation()=='i')
					strcpy(sr2,"Internal");
					else
					strcpy(sr2,"Front Facing");

					printf("\n%-10d %-10s %.2f %-10s %10d %-10s %10c %10s %.2f",index,cm1.pname,cm1.psize,sr1,cm1.get_shops(),sr2,toupper(cm1.purchasetype),cm1.get_zonename(),cm1.baserate);
					}//print statement
					f3ptr.read((char*)&cm1,sizeof(commercial));
				}
				f3ptr.clear();
				cout<<"\nEnter desired property number: ";
				cin>>cho1;
				while(!(cho1>=1 && cho1<=count))
				{
					cout<<"\nInvalid entry. Enter valid property number: ";
					cin>>cho1;
				}
				cho1-=1;
				
				cout<<"\nProperty details: \n";
				comarr[cho1].displaydetails();
				cout<<"\nBuying Party: \nCustomer Name: "<<this->fullname<<"\nContact Information: \nPhone No.: "<<this->contactno<<"\nEmail: "<<this->useremail;
				comarr[cho1].viewcontract('r');
				cout<<"\nPress any key to continue...";
				getchar();
				getchar();
			}
		}
		else if(pchoice==1)
		{
				int rc;//hosues and flats
			cout<<"\nEnter: \n1. For Houses\n2. For Flats: ";
			cin>>rc;
			while(rc!=1 && rc!=2)
			{
				cout<<"\nInvalid entry. Enter: \n1. For Houses\n2. For Flats: ";
				cin>>rc;
			}
			if(rc==1)
			{
				house cm1,cm2;
			f1ptr.clear();
			f1ptr.read((char*)&cm1,sizeof(house));
			while(!f1ptr.eof())
			{
				if(cm1.ownerid==(this->custid) && tolower(cm1.purchasetype)=='r')
				count++;
				f1ptr.read((char*)&cm1,sizeof(house));
			}
			if(count==0)
			{
				cout<<"\nNo available residential properties to display.\nPress any key to continue...";
				f3ptr.close();
				f2ptr.close();
				f1ptr.close();
				getchar();
				getchar();
				return 0;
			}
			else
			{
				int index=0;
				f1ptr.clear();
				f1ptr.seekg(0,ios::beg);
				house comarr[count];
				cout<<"\nSerial No. | Name | Size (Sq. Guz) | Available | Rooms | House Type | Purchase Type |  Floors | Furnished | Buy Price (Rs.)\n";
				f1ptr.read((char*)&cm1,sizeof(house));
				while(!f1ptr.eof())
				{
					if(cm1.ownerid==(this->custid) && tolower(cm1.purchasetype)=='r')
					{
						comarr[index]=cm1;
						index+=1;
						if(cm1.available==1)
						strcpy(sr1,"YES");
						else
						strcpy(sr1,"NO");
						if(cm1.furnished==1)
						strcpy(sr2,"YES");
						else
						strcpy(sr2,"NO");
						
						printf("\n%-10d %-10s %.2f %-10s %10d %-10s %10c %10d %-10s %.2f",index,cm1.pname,cm1.psize,sr1,cm1.rooms,cm1.get_housetype(),toupper(cm1.purchasetype),cm1.floors,sr2,cm1.baserate);//co1.pname<<co1.psize<<sr1<<co1.get_shops()<<toupper(co1.purchasetype)<<co1.get_zonename()<<co1.baserate;
					}
					f1ptr.read((char*)&cm1,sizeof(house));
				}
				f1ptr.clear();
				cout<<"\nEnter desired property number: ";
				cin>>cho1;
				while(!(cho1>=1 && cho1<=count))
				{
					cout<<"\nInvalid entry. Enter valid property number: ";
					cin>>cho1;
				}
				cho1-=1;
				
				cout<<"\nProperty details: \n";
				comarr[cho1].displaydetails();
				cout<<"\nBuying Party: \nCustomer Name: "<<this->fullname<<"\nContact Information: \nPhone No.: "<<this->contactno<<"\nEmail: "<<this->useremail;
				comarr[cho1].viewcontract('r');
				cout<<"\nPress any key to continue...";
				getchar();
				getchar();
			}
			}
			else
			{
				flat cm1,cm2;
				f2ptr.clear();
				f2ptr.seekg(0,ios::beg);
				f2ptr.read((char*)&cm1,sizeof(flat));
			while(!f2ptr.eof())
			{
				if(cm1.ownerid==(this->custid) && tolower(cm1.purchasetype)=='r')
				count++;
				f2ptr.read((char*)&cm1,sizeof(flat));
			}
			if(count==0)
			{
				cout<<"\nNo available residential properties to display.\nPress any key to continue...";
				f3ptr.close();
				f2ptr.close();
				f1ptr.close();
				getchar();
				getchar();
				return 0;
			}
			else
			{
				int index=0;
				char sr3[50],sr4[50];
				f2ptr.clear();
				f2ptr.seekg(0,ios::beg);
				flat comarr[count];
				f2ptr.read((char*)&cm1,sizeof(flat));
				cout<<"\nSerial No. | Name | Size (Sq. Guz) | Available | Rooms | Parking | Purchase Type |  Elevator | Furnished | Buy Price (Rs.)\n";
				while(!f2ptr.eof())
				{
					if(cm1.ownerid==(this->custid) && tolower(cm1.purchasetype)=='r')
					{
						comarr[index]=cm1;
						index+=1;
						if(cm1.available==1)
						strcpy(sr1,"YES");
						else
						strcpy(sr1,"NO");
						if(cm1.furnished==1)
						strcpy(sr2,"YES");
						else
						strcpy(sr2,"NO");
						if(cm1.get_parking()==1)
						strcpy(sr3,"YES");
						else
						strcpy(sr3,"NO");
						if(cm1.get_elevator()==1)
						strcpy(sr4,"YES");
						else
						strcpy(sr4,"NO");
						
						printf("\n%-10d %-10s %.2f %-10s %10d %-10s %10c %-10s %-10s %.2f",index,cm1.pname,cm1.psize,sr1,cm1.rooms,sr3,toupper(cm1.purchasetype),sr4,sr2,cm1.baserate);
					}
					f2ptr.read((char*)&cm1,sizeof(flat));
				}
				f2ptr.clear();
				cout<<"\nEnter desired property number: ";
				cin>>cho1;
				while(!(cho1>=1 && cho1<=count))
				{
					cout<<"\nInvalid entry. Enter valid property number: ";
					cin>>cho1;
				}
				cho1-=1;
				
				cout<<"\nProperty details: \n";
				comarr[cho1].displaydetails();
				cout<<"\nBuying Party: \nCustomer Name: "<<this->fullname<<"\nContact Information: \nPhone No.: "<<this->contactno<<"\nEmail: "<<this->useremail;
				comarr[cho1].viewcontract('r');
				cout<<"\nPress any key to continue...";
				getchar();
			getchar();
			}	
			}//
		}
		f1ptr.close();
		f2ptr.close();
		f3ptr.close();
	}
	//view bought properties
	int view_bought()
	{
		int pchoice,cho1;
		fstream f1ptr,f2ptr,f3ptr;
		string str1="House.dat";
		string str2="Flats.dat";
		string str3="Commercial.dat";
		
		f1ptr.open(str1.c_str(),ios::binary|ios::in|ios::out);
		f2ptr.open(str2.c_str(),ios::binary|ios::in|ios::out);
		f3ptr.open(str3.c_str(),ios::binary|ios::in|ios::out);
		f1ptr.seekg(0,ios::end);
		f2ptr.seekg(0,ios::end);
		f3ptr.seekg(0,ios::end);
		
		if(f1ptr.tellg()==0 && f2ptr.tellg()==0 && f3ptr.tellg()==0)
		{
			cout<<"\nError. No records to display.\n\n";
		}
		
		f1ptr.seekg(0,ios::beg);
		f2ptr.seekg(0,ios::beg);
		f3ptr.seekg(0,ios::beg);
		int count=0;
		int p1;
		char sr1[20],sr2[20];
		cout<<"\n**********PROPERTIES**********\n\n\n";
		cout<<"******PROPERTY TYPE******\n\n1. RESIDENTIAL\n2. COMMERCIAL\nEnter your choice: ";
		cin>>pchoice;
		while(pchoice<1 || pchoice>2)
		{
				cout<<"\nInvalid entry! Enter valid choice: ";
				cin>>pchoice;
		}
		if(pchoice==2)
		{
			commercial cm1,cm2;
			f3ptr.clear();
			f3ptr.read((char*)&cm1,sizeof(commercial));
			while(!f3ptr.eof())
			{
				if(cm1.ownerid==(this->custid) && tolower(cm1.purchasetype)=='b')
				count++;
				f3ptr.read((char*)&cm1,sizeof(commercial));
			}
			if(count==0)
			{
				cout<<"\nNo commercial properties to display.\nPress any key to continue...";
				f3ptr.close();
				f2ptr.close();
				f1ptr.close();
				getchar();
				getchar();
				return 1;
				
			}
			else
			{
				int index=0;
				f3ptr.clear();
				f3ptr.seekg(0,ios::beg);
				commercial comarr[count];
				f3ptr.read((char*)&cm1,sizeof(commercial));
				
				cout<<"\nSerial No. | Name | Size | Available | Shops | Facing Type | Purchase Type | Commercial Zone | Buy Price (Rs.)\n";
				while(!f3ptr.eof())
				{
					if(cm1.ownerid==(this->custid) && tolower(cm1.purchasetype)=='b')
					{
					comarr[index]=cm1;
					index+=1;
					strcpy(sr1,"YES");
					
					if(cm1.get_shoplocation()=='i')
					strcpy(sr2,"Internal");
					else
					strcpy(sr2,"Front Facing");

					printf("\n%-10d %-10s %.2f %-10s %10d %-10s %10c %10s %.2f",index,cm1.pname,cm1.psize,sr1,cm1.get_shops(),sr2,toupper(cm1.purchasetype),cm1.get_zonename(),cm1.baserate);
					}//print statement
					f3ptr.read((char*)&cm1,sizeof(commercial));
				}
				f3ptr.clear();
				cout<<"\nEnter desired property number: ";
				cin>>cho1;
				while(!(cho1>=1 && cho1<=count))
				{
					cout<<"\nInvalid entry. Enter valid property number: ";
					cin>>cho1;
				}
				cho1-=1;
				
				cout<<"\nProperty details: \n";
				comarr[cho1].displaydetails();
				cout<<"\nBuying Party: \nCustomer Name: "<<this->fullname<<"\nContact Information: \nPhone No.: "<<this->contactno<<"\nEmail: "<<this->useremail;
				comarr[cho1].viewcontract('b');
				cout<<"\nPress any key to continue...";
				getchar();
				getchar();
			}
		}
		else if(pchoice==1)
		{
				int rc;//hosues and flats
			cout<<"\nEnter: \n1. For Houses\n2. For Flats: ";
			cin>>rc;
			while(rc!=1 && rc!=2)
			{
				cout<<"\nInvalid entry. Enter: \n1. For Houses\n2. For Flats: ";
				cin>>rc;
			}
			if(rc==1)
			{
				house cm1,cm2;
			f1ptr.clear();
			f1ptr.read((char*)&cm1,sizeof(house));
			while(!f1ptr.eof())
			{
				if(cm1.ownerid==(this->custid) && tolower(cm1.purchasetype)=='b')
				count++;
				f1ptr.read((char*)&cm1,sizeof(house));
			}
			if(count==0)
			{
				cout<<"\nNo available residential properties to display.\nPress any key to continue...";
				f3ptr.close();
				f2ptr.close();
				f1ptr.close();
				getchar();
				getchar();
				return 0;
			}
			else
			{
				int index=0;
				f1ptr.clear();
				f1ptr.seekg(0,ios::beg);
				house comarr[count];
				cout<<"\nSerial No. | Name | Size (Sq. Guz) | Available | Rooms | House Type | Purchase Type |  Floors | Furnished | Buy Price (Rs.)\n";
				f1ptr.read((char*)&cm1,sizeof(house));
				while(!f1ptr.eof())
				{
					if(cm1.ownerid==(this->custid) && tolower(cm1.purchasetype)=='b')
					{
						comarr[index]=cm1;
						index+=1;
						if(cm1.available==1)
						strcpy(sr1,"YES");
						else
						strcpy(sr1,"NO");
						if(cm1.furnished==1)
						strcpy(sr2,"YES");
						else
						strcpy(sr2,"NO");
						
						printf("\n%-10d %-10s %.2f %-10s %10d %-10s %10c %10d %-10s %.2f",index,cm1.pname,cm1.psize,sr1,cm1.rooms,cm1.get_housetype(),toupper(cm1.purchasetype),cm1.floors,sr2,cm1.baserate);//co1.pname<<co1.psize<<sr1<<co1.get_shops()<<toupper(co1.purchasetype)<<co1.get_zonename()<<co1.baserate;
					}
					f1ptr.read((char*)&cm1,sizeof(house));
				}
				f1ptr.clear();
				cout<<"\nEnter desired property number: ";
				cin>>cho1;
				while(!(cho1>=1 && cho1<=count))
				{
					cout<<"\nInvalid entry. Enter valid property number: ";
					cin>>cho1;
				}
				cho1-=1;
				
				cout<<"\nProperty details: \n";
				comarr[cho1].displaydetails();
				cout<<"\nBuying Party: \nCustomer Name: "<<this->fullname<<"\nContact Information: \nPhone No.: "<<this->contactno<<"\nEmail: "<<this->useremail;
				comarr[cho1].viewcontract('b');
				cout<<"\nPress any key to continue...";
				getchar();
				getchar();
			}
			}
			else
			{
				flat cm1,cm2;
				f2ptr.clear();
				f2ptr.read((char*)&cm1,sizeof(flat));
			while(!f2ptr.eof())
			{
				if(cm1.ownerid==(this->custid) && tolower(cm1.purchasetype)=='b')
				count++;
				f2ptr.read((char*)&cm1,sizeof(flat));
			}
			if(count==0)
			{
				cout<<"\nNo available residential properties to display.\nPress any key to continue...";
				f3ptr.close();
				f2ptr.close();
				f1ptr.close();
				getchar();
				getchar();
				return 0;
			}
			else
			{
				int index=0;
				char sr3[50],sr4[50];
				f2ptr.clear();
				f2ptr.seekg(0,ios::beg);
				flat comarr[count];
				f2ptr.read((char*)&cm1,sizeof(flat));
				cout<<"\nSerial No. | Name | Size (Sq. Guz) | Available | Rooms | Parking | Purchase Type |  Elevator | Furnished | Buy Price (Rs.)\n";
				while(!f2ptr.eof())
				{
					if(cm1.ownerid==(this->custid) && tolower(cm1.purchasetype)=='b')
					{
						comarr[index]=cm1;
						index+=1;
						if(cm1.available==1)
						strcpy(sr1,"YES");
						else
						strcpy(sr1,"NO");
						if(cm1.furnished==1)
						strcpy(sr2,"YES");
						else
						strcpy(sr2,"NO");
						if(cm1.get_parking()==1)
						strcpy(sr3,"YES");
						else
						strcpy(sr3,"NO");
						if(cm1.get_elevator()==1)
						strcpy(sr4,"YES");
						else
						strcpy(sr4,"NO");
						
						printf("\n%-10d %-10s %.2f %-10s %10d %-10s %10c %-10s %-10s %.2f",index,cm1.pname,cm1.psize,sr1,cm1.rooms,sr3,toupper(cm1.purchasetype),sr4,sr2,cm1.baserate);
					}
					f2ptr.read((char*)&cm1,sizeof(flat));
				}
				f2ptr.clear();
				cout<<"\nEnter desired property number: ";
				cin>>cho1;
				while(!(cho1>=1 && cho1<=count))
				{
					cout<<"\nInvalid entry. Enter valid property number: ";
					cin>>cho1;
				}
				cho1-=1;
				
				cout<<"\nProperty details: \n";
				comarr[cho1].displaydetails();
				cout<<"\nBuying Party: \nCustomer Name: "<<this->fullname<<"\nContact Information: \nPhone No.: "<<this->contactno<<"\nEmail: "<<this->useremail;
				comarr[cho1].viewcontract('b');
				cout<<"\nPress any key to continue...";
				getchar();
				getchar();
			
			}	
			}//
		}
			f1ptr.close();
		f2ptr.close();
		f3ptr.close();
	}
	
	//void manage_notifications();//view, clear
	
	//displays account details and provides optional password updation
	//customer can also update his budget through this portal
	void view_accountdetails()
	{
		int ach;
		display1();
		if(this->budget==-1)
		{
			cout<<"\nAccount Details:\n\nCustomer ID: "<<custid<<"\nAccount total: Rs. "<<acctotal<<"\nBuy Total: Rs. "<<buytotal<<"\nRent Total: Rs. "<<renttotal<<"\nTotal Properties: "<<totalprops<<"\nCurrent Budget: Disabled\n";
		}
		else
		cout<<"\nAccount Details:\n\nCustomer ID: "<<custid<<"\nAccount total: Rs. "<<acctotal<<"\nBuy Total: Rs. "<<buytotal<<"\nRent Total: Rs. "<<renttotal<<"\nTotal Properties: "<<totalprops<<"\nCurrent Budget: Rs."<<budget<<"\n";
		cout<<"\nDo you wish to update:\n1. Your Password\n2. Your Budget\n3. None? Enter your choice: ";
		cin>>ach;
		while(ach<1 || ach>3)
		{
			cout<<"\nInvalid entry. Enter valid choice: ";
			cin>>ach;
		}
		customer cg1;
		fstream aptr;	
		string filename="CustomerInfo.dat";
		aptr.open(filename.c_str(),ios::binary|ios::in|ios::out);
		if(!aptr)
		{
			cout<<"\nError opening file\n";
			exit(1);
		}
		
		if(ach==1)
		{
			aptr.read((char*)&cg1,sizeof(customer));
			while(!aptr.eof())
			{
				if((this->custid)==cg1.get_custid())
				{
					break;
				}
				aptr.read((char*)&cg1,sizeof(customer));
			}
			fflush(stdin);
			cout<<"\nEnter a unique password: ";
  			cin.getline(this->upass,50);
  			while(checkpass(this->upass)!=1)
			{
				cout<<"\nInvalid password entered! Password must:\n\t*Be at least 8 characters long\n\t*Have at least 1 capital letter\n\nEnter password: ";
				cin.getline(this->upass,50);
			}
			cg1.set_upass(upass);
			this->copyobj(cg1);
			aptr.clear();
			aptr.seekp(-sizeof(customer),ios::cur);
			aptr.write((char*)&cg1,sizeof(customer));
			aptr.close();
			cout<<"\nAccount password successfully updated!. Press any key to continue...";
			getchar();
			getchar();
			
		}
		else if(ach==2)
		{
			aptr.read((char*)&cg1,sizeof(customer));
			while(!aptr.eof())
			{
				if((this->custid)==cg1.get_custid())
				{
					break;
				}
				aptr.read((char*)&cg1,sizeof(customer));
			}
			cout<<"\nEnter new budget (-1 to disable budget): ";
			cin>>budget;
			if(budget==-1)
			cout<<"\nBudget Disabled.\n";
			else
			{
				while(budget<5000000)
				{
					cout<<"\nInvalid entry! Enter at least Rs. 5000000 for budget: ";
					cin>>budget;
				}
			}
			cg1.set_budget(this->budget);
			this->copyobj(cg1);
			aptr.clear();
			aptr.seekp(-sizeof(customer),ios::cur);
			aptr.write((char*)&cg1,sizeof(customer));
			aptr.close();
			cout<<"\nAccount budget successfully updated!. Press any key to continue...";
			getchar();
			getchar();
		}
		else
		{
			cout<<"\nPassword/Budget unchanged.\n\nPress any key to continue...";
			getchar();
			getchar();
		}
		
	}
	
	//add an existing property to the wishlist
	int update_wishlist()
	{
		int pchoice,cho1;
		fstream f1ptr,f2ptr,f3ptr;
		string str1="House.dat";
		string str2="Flats.dat";
		string str3="Commercial.dat";
		
		f1ptr.open(str1.c_str(),ios::binary|ios::in|ios::out);
		f2ptr.open(str2.c_str(),ios::binary|ios::in|ios::out);
		f3ptr.open(str3.c_str(),ios::binary|ios::in|ios::out);
		f1ptr.seekg(0,ios::end);
		f2ptr.seekg(0,ios::end);
		f3ptr.seekg(0,ios::end);
		
		if(f1ptr.tellg()==0 && f2ptr.tellg()==0 && f3ptr.tellg()==0)
		{
			cout<<"\nError. No records to display.\n\n";
		}
		
		f1ptr.seekg(0,ios::beg);
		f2ptr.seekg(0,ios::beg);
		f3ptr.seekg(0,ios::beg);
		int count=0;
		int p1;
		char sr1[20],sr2[20];
		cout<<"\n**********PROPERTIES**********\n\n\n";
		cout<<"******PROPERTY TYPE******\n\n1. RESIDENTIAL\n2. COMMERCIAL\nEnter your choice: ";
		cin>>pchoice;
		while(pchoice<1 || pchoice>2)
		{
				cout<<"\nInvalid entry! Enter valid choice: ";
				cin>>pchoice;
		}
		if(pchoice==2)
		{
			commercial cm1,cm2;
			f3ptr.clear();
			f3ptr.read((char*)&cm1,sizeof(commercial));
			while(!f3ptr.eof())
			{
				if(cm1.available==1)
				count++;
				f3ptr.read((char*)&cm1,sizeof(commercial));
			}
			if(count==0)
			{
				cout<<"\nNo available commercial properties to display.\nPress any key to continue...";
				f3ptr.close();
				f2ptr.close();
				f1ptr.close();
				getchar();
				getchar();
				return 0;
			}
			else
			{
				int index=0;
				f3ptr.clear();
				f3ptr.seekg(0,ios::beg);
				commercial comarr[count];
				f3ptr.read((char*)&cm1,sizeof(commercial));
				
				cout<<"\nSerial No. | Name | Size | Available | Shops | Facing Type | Purchase Type | Commercial Zone | Buy Price (Rs.)\n";
				while(!f3ptr.eof())
				{
					if(cm1.available==1)
					{
					comarr[index]=cm1;
					index+=1;
					strcpy(sr1,"YES");
					
					if(cm1.get_shoplocation()=='i')
					strcpy(sr2,"Internal");
					else
					strcpy(sr2,"Front Facing");

					printf("\n%-10d %-10s %.2f %-10s %10d %-10s %10c %10s %.2f",index,cm1.pname,cm1.psize,sr1,cm1.get_shops(),sr2,toupper(cm1.purchasetype),cm1.get_zonename(),cm1.baserate);
					}//print statement
					f3ptr.read((char*)&cm1,sizeof(commercial));
				}
				f3ptr.clear();
				cout<<"\nEnter desired property number: ";
				cin>>cho1;
				while(!(cho1>=1 && cho1<=count))
				{
					cout<<"\nInvalid entry. Enter valid property number: ";
					cin>>cho1;
				}
				cho1-=1;
				
				cout<<"\nProperty details: \n";
				comarr[cho1].displaydetails();//
				comarr[cho1].addto_wishlist(custid);
				f3ptr.clear();
				f3ptr.seekg(0,ios::beg);
				f3ptr.read((char*)&cm2,sizeof(commercial));
				while(!f3ptr.eof())
				{
					if(cm2.get_propertyid()==comarr[cho1].get_propertyid())
					{
						break;
					}
					f3ptr.read((char*)&cm2,sizeof(commercial));
				}
				f3ptr.seekp(-sizeof(commercial),ios::cur);
				f3ptr.write((char*)&comarr[cho1],sizeof(commercial));
				cout<<"\nProperty successfully added to wish list.\nPress any key to continue...";
				getchar();
				getchar();
			}
		}
		else if(pchoice==1)
		{
			int rc;//hosues and flats
			cout<<"\nEnter: \n1. For Houses\n2. For Flats: ";
			cin>>rc;
			while(rc!=1 && rc!=2)
			{
					cout<<"\nInvalid entry. Enter: \n1. For Houses\n2. For Flats: ";
					cin>>rc;
			}
			if(rc==1)
			{
			house cm1,cm2;
			f1ptr.clear();
			f1ptr.read((char*)&cm1,sizeof(house));
			while(!f1ptr.eof())
			{
				if(cm1.available==1)
				count++;
				f1ptr.read((char*)&cm1,sizeof(house));
			}
			if(count==0)
			{
				cout<<"\nNo available residential properties to display.\nPress any key to continue...";
				f3ptr.close();
				f2ptr.close();
				f1ptr.close();
				getchar();
				getchar();
				return 0;
			}
			else
			{
				int index=0;
				f1ptr.clear();
				f1ptr.seekg(0,ios::beg);
				house comarr[count];
				cout<<"\nSerial No. | Name | Size (Sq. Guz) | Available | Rooms | House Type | Purchase Type |  Floors | Furnished | Buy Price (Rs.)\n";
				f1ptr.read((char*)&cm1,sizeof(house));
				while(!f1ptr.eof())
				{
					if(cm1.available==1)
					{
						comarr[index]=cm1;
						index+=1;
						if(cm1.available==1)
						strcpy(sr1,"YES");
						else
						strcpy(sr1,"NO");
						if(cm1.furnished==1)
						strcpy(sr2,"YES");
						else
						strcpy(sr2,"NO");
						
						printf("\n%-10d %-10s %.2f %-10s %10d %-10s %10c %10d %-10s %.2f",index,cm1.pname,cm1.psize,sr1,cm1.rooms,cm1.get_housetype(),toupper(cm1.purchasetype),cm1.floors,sr2,cm1.baserate);//co1.pname<<co1.psize<<sr1<<co1.get_shops()<<toupper(co1.purchasetype)<<co1.get_zonename()<<co1.baserate;
					}
					f1ptr.read((char*)&cm1,sizeof(house));
				}
				f1ptr.clear();
				cout<<"\nEnter desired property number: ";
				cin>>cho1;
				while(!(cho1>=1 && cho1<=count))
				{
					cout<<"\nInvalid entry. Enter valid property number: ";
					cin>>cho1;
				}
				cho1-=1;
				
				cout<<"\nProperty details: \n";
				comarr[cho1].displaydetails();
				comarr[cho1].addto_wishlist(custid);
				f1ptr.clear();
				f1ptr.seekg(0,ios::beg);
				f1ptr.read((char*)&cm2,sizeof(house));
				while(!f1ptr.eof())
				{
					if(cm2.propertyid==comarr[cho1].propertyid)
					{
						break;
					}
					f1ptr.read((char*)&cm2,sizeof(house));
				}
				f1ptr.seekp(-sizeof(house),ios::cur);
				f1ptr.write((char*)&comarr[cho1],sizeof(house));
				cout<<"\nProperty successfully added to wish list.\nPress any key to continue...";
				getchar();
				getchar();
			
			}
			}
			else if(rc==2)
			{
			flat cm1,cm2;
			f2ptr.clear();
			f2ptr.read((char*)&cm1,sizeof(flat));
			while(!f2ptr.eof())
			{
				if(cm1.available==1)
				count++;
				f2ptr.read((char*)&cm1,sizeof(flat));
			}
			if(count==0)
			{
				cout<<"\nNo available residential properties to display.\nPress any key to continue...";
				f3ptr.close();
				f2ptr.close();
				f1ptr.close();
				getchar();
				getchar();
				return 0;
			}
			else
			{
				int index=0;
				char sr3[50],sr4[50];
				f2ptr.clear();
				f2ptr.seekg(0,ios::beg);
				flat comarr[count];
				f2ptr.read((char*)&cm1,sizeof(flat));
				cout<<"\nSerial No. | Name | Size (Sq. Guz) | Available | Rooms | Parking | Purchase Type |  Elevator | Furnished | Buy Price (Rs.)\n";
				while(!f2ptr.eof())
				{
					if(cm1.available==1)
					{
						comarr[index]=cm1;
						index+=1;
						if(cm1.available==1)
						strcpy(sr1,"YES");
						else
						strcpy(sr1,"NO");
						if(cm1.furnished==1)
						strcpy(sr2,"YES");
						else
						strcpy(sr2,"NO");
						if(cm1.get_parking()==1)
						strcpy(sr3,"YES");
						else
						strcpy(sr3,"NO");
						if(cm1.get_elevator()==1)
						strcpy(sr4,"YES");
						else
						strcpy(sr4,"NO");
						
						printf("\n%-10d %-10s %.2f %-10s %10d %-10s %10c %-10s %-10s %.2f",index,cm1.pname,cm1.psize,sr1,cm1.rooms,sr3,toupper(cm1.purchasetype),sr4,sr2,cm1.baserate);
					}
					f2ptr.read((char*)&cm1,sizeof(flat));
				}
				f2ptr.clear();
				cout<<"\nEnter desired property number: ";
				cin>>cho1;
				while(!(cho1>=1 && cho1<=count))
				{
					cout<<"\nInvalid entry. Enter valid property number: ";
					cin>>cho1;
				}
				cho1-=1;
				
				cout<<"\nProperty details: \n";
				comarr[cho1].displaydetails();
				comarr[cho1].addto_wishlist(custid);
				f2ptr.clear();
				f2ptr.seekg(0,ios::beg);
				f2ptr.read((char*)&cm2,sizeof(flat));
				while(!f2ptr.eof())
				{
					if(cm2.propertyid==comarr[cho1].propertyid)
					{
						break;
					}
					f2ptr.read((char*)&cm2,sizeof(flat));
				}
				f2ptr.seekp(-sizeof(flat),ios::cur);
				f2ptr.write((char*)&comarr[cho1],sizeof(flat));
				cout<<"\nProperty successfully added to wish list.\nPress any key to continue...";
				getchar();
				getchar();
			
			}	
			}
		}
		f3ptr.close();
		f2ptr.close();
		f1ptr.close();
	}
	
	//view wishlists for properties
	int view_wishlist()
	{
		int pchoice,cho1;
		fstream f1ptr,f2ptr,f3ptr;
		string str1="House.dat";
		string str2="Flats.dat";
		string str3="Commercial.dat";
		
		f1ptr.open(str1.c_str(),ios::binary|ios::in|ios::out);
		f2ptr.open(str2.c_str(),ios::binary|ios::in|ios::out);
		f3ptr.open(str3.c_str(),ios::binary|ios::in|ios::out);
		f1ptr.seekg(0,ios::end);
		f2ptr.seekg(0,ios::end);
		f3ptr.seekg(0,ios::end);
		
		if(f1ptr.tellg()==0 && f2ptr.tellg()==0 && f3ptr.tellg()==0)
		{
			cout<<"\nError. No records to display.\n\n";
		}
		
		f1ptr.seekg(0,ios::beg);
		f2ptr.seekg(0,ios::beg);
		f3ptr.seekg(0,ios::beg);
		int count=0;
		int p1;
		char sr1[20],sr2[20];
		cout<<"\n**********PROPERTIES**********\n\n\n";
		cout<<"******PROPERTY TYPE******\n\n1. RESIDENTIAL\n2. COMMERCIAL\nEnter your choice: ";
		cin>>pchoice;
		while(pchoice<1 || pchoice>2)
		{
				cout<<"\nInvalid entry! Enter valid choice: ";
				cin>>pchoice;
		}
		if(pchoice==2)
		{
			commercial cm1,cm2;
			f3ptr.clear();
			f3ptr.read((char*)&cm1,sizeof(commercial));
			while(!f3ptr.eof())
			{
				if((cm1.available==1 && cm1.searchlist(custid)==1) || (cm1.ownerid==custid && cm1.searchlist(custid)==1))
				count++;
				f3ptr.read((char*)&cm1,sizeof(commercial));
			}
			if(count==0)
			{
				cout<<"\nNo available commercial properties to display.\nPress any key to continue...";
				f3ptr.close();
				f2ptr.close();
				f1ptr.close();
				getchar();
				getchar();
				return 1;
				
			}
			else
			{
				int index=0;
				f3ptr.clear();
				f3ptr.seekg(0,ios::beg);
				commercial comarr[count];
				f3ptr.read((char*)&cm1,sizeof(commercial));
				
				cout<<"\nSerial No. | Name | Size | Available | Shops | Facing Type | Purchase Type | Commercial Zone | Buy Price (Rs.)\n";
				while(!f3ptr.eof())
				{
					if(cm1.available==1 && cm1.searchlist(custid)==1 || (cm1.ownerid==custid && cm1.searchlist(custid)==1))
					{
					comarr[index]=cm1;
					index+=1;
					strcpy(sr1,"YES");
					
					if(cm1.get_shoplocation()=='i')
					strcpy(sr2,"Internal");
					else
					strcpy(sr2,"Front Facing");

					printf("\n%-10d %-10s %.2f %-10s %10d %-10s %10c %10s %.2f",index,cm1.pname,cm1.psize,sr1,cm1.get_shops(),sr2,toupper(cm1.purchasetype),cm1.get_zonename(),cm1.baserate);
					}//print statement
					f3ptr.read((char*)&cm1,sizeof(commercial));
				}
				f3ptr.clear();
				cout<<"\nEnter desired property number: ";
				cin>>cho1;
				while(!(cho1>=1 && cho1<=count))
				{
					cout<<"\nInvalid entry. Enter valid property number: ";
					cin>>cho1;
				}
				cho1-=1;
				
				cout<<"\nProperty details: \n";
				comarr[cho1].displaydetails();
				cout<<"\nPress any key to continue...";
				getchar();
				getchar();
			}
		}
		else
		{
			int rc;//hosues and flats
			cout<<"\nEnter: \n1. For Houses\n2. For Flats: ";
			cin>>rc;
			while(rc!=1 && rc!=2)
			{
				cout<<"\nInvalid entry. Enter: \n1. For Houses\n2. For Flats: ";
				cin>>rc;
			}
			if(rc==1)
			{
				house cm1,cm2;
			f1ptr.clear();
			f1ptr.read((char*)&cm1,sizeof(house));
			while(!f1ptr.eof())
			{
				if(cm1.available==1 && cm1.searchlist(custid)==1 || (cm1.ownerid==custid && cm1.searchlist(custid)==1))
				count++;
				f1ptr.read((char*)&cm1,sizeof(house));
			}
			if(count==0)
			{
				cout<<"\nNo available residential properties to display.\nPress any key to continue...";
				f3ptr.close();
				f2ptr.close();
				f1ptr.close();
				getchar();
				getchar();
				return 0;
			}
			else
			{
				int index=0;
				f1ptr.clear();
				f1ptr.seekg(0,ios::beg);
				house comarr[count];
				cout<<"\nSerial No. | Name | Size (Sq. Guz) | Available | Rooms | House Type | Purchase Type |  Floors | Furnished | Buy Price (Rs.)\n";
				f1ptr.read((char*)&cm1,sizeof(house));
				while(!f1ptr.eof())
				{
					if(cm1.available==1 && cm1.searchlist(custid)==1 || (cm1.ownerid==custid && cm1.searchlist(custid)==1))
					{
						comarr[index]=cm1;
						index+=1;
						if(cm1.available==1)
						strcpy(sr1,"YES");
						else
						strcpy(sr1,"NO");
						if(cm1.furnished==1)
						strcpy(sr2,"YES");
						else
						strcpy(sr2,"NO");
						
						printf("\n%-10d %-10s %.2f %-10s %10d %-10s %10c %10d %-10s %.2f",index,cm1.pname,cm1.psize,sr1,cm1.rooms,cm1.get_housetype(),toupper(cm1.purchasetype),cm1.floors,sr2,cm1.baserate);//co1.pname<<co1.psize<<sr1<<co1.get_shops()<<toupper(co1.purchasetype)<<co1.get_zonename()<<co1.baserate;
					}
					f1ptr.read((char*)&cm1,sizeof(house));
				}
				f1ptr.clear();
				cout<<"\nEnter desired property number: ";
				cin>>cho1;
				while(!(cho1>=1 && cho1<=count))
				{
					cout<<"\nInvalid entry. Enter valid property number: ";
					cin>>cho1;
				}
				cho1-=1;
				
				cout<<"\nProperty details: \n";
				comarr[cho1].displaydetails();
				cout<<"\nPress any key to continue...";
				getchar();
			}
			}
			else
			{
				flat cm1,cm2;
				f2ptr.clear();
				f2ptr.read((char*)&cm1,sizeof(flat));
			while(!f2ptr.eof())
			{
				if(cm1.available==1 && cm1.searchlist(custid)==1 || (cm1.ownerid==custid && cm1.searchlist(custid)==1))
				count++;
				f2ptr.read((char*)&cm1,sizeof(flat));
			}
			if(count==0)
			{
				cout<<"\nNo available residential properties to display.\nPress any key to continue...";
				f3ptr.close();
				f2ptr.close();
				f1ptr.close();
				getchar();
				getchar();
				return 0;
			}
			else
			{
				int index=0;
				char sr3[50],sr4[50];
				f2ptr.clear();
				f2ptr.seekg(0,ios::beg);
				flat comarr[count];
				f2ptr.read((char*)&cm1,sizeof(flat));
				cout<<"\nSerial No. | Name | Size (Sq. Guz) | Available | Rooms | Parking | Purchase Type |  Elevator | Furnished | Buy Price (Rs.)\n";
				while(!f2ptr.eof())
				{
					if(cm1.available==1 && cm1.searchlist(custid)==1 || (cm1.ownerid==custid && cm1.searchlist(custid)==1))
					{
						comarr[index]=cm1;
						index+=1;
						if(cm1.available==1)
						strcpy(sr1,"YES");
						else
						strcpy(sr1,"NO");
						if(cm1.furnished==1)
						strcpy(sr2,"YES");
						else
						strcpy(sr2,"NO");
						if(cm1.get_parking()==1)
						strcpy(sr3,"YES");
						else
						strcpy(sr3,"NO");
						if(cm1.get_elevator()==1)
						strcpy(sr4,"YES");
						else
						strcpy(sr4,"NO");
						
						printf("\n%-10d %-10s %.2f %-10s %10d %-10s %10c %-10s %-10s %.2f",index,cm1.pname,cm1.psize,sr1,cm1.rooms,sr3,toupper(cm1.purchasetype),sr4,sr2,cm1.baserate);
					}
					f2ptr.read((char*)&cm1,sizeof(flat));
				}
				f2ptr.clear();
				cout<<"\nEnter desired property number: ";
				cin>>cho1;
				while(!(cho1>=1 && cho1<=count))
				{
					cout<<"\nInvalid entry. Enter valid property number: ";
					cin>>cho1;
				}
				cho1-=1;
				
				cout<<"\nProperty details: \n";
				comarr[cho1].displaydetails();
				cout<<"\nPress any key to continue...";
				getchar();
			
			}	
			}//
		}
		f3ptr.close();
		f2ptr.close();
		f1ptr.close();
		cout<<"\nPress any key to continue...";
		getchar();
		getchar();
	}
	
	void add_comment();
	
	//buy or rent available* properties
	int buy_property()
	{
		char cho;
		char fchoice;
		cout<<"\n\nB. Buy\nR. Rent\nEnter your choice: ";
		cin>>cho;
		while(tolower(cho)!='b' && tolower(cho)!='r')
		{
			cout<<"\nInvalid entry. Enter valid choice: ";
			cin>>cho;
		}
		
		int pchoice,cho1;
		fstream f1ptr,f2ptr,f3ptr;
		string str1="House.dat";
		string str2="Flats.dat";
		string str3="Commercial.dat";
		
		f1ptr.open(str1.c_str(),ios::binary|ios::in|ios::out);
		f2ptr.open(str2.c_str(),ios::binary|ios::in|ios::out);
		f3ptr.open(str3.c_str(),ios::binary|ios::in|ios::out);
		f1ptr.seekg(0,ios::end);
		f2ptr.seekg(0,ios::end);
		f3ptr.seekg(0,ios::end);
		
		if(f1ptr.tellg()==0 && f2ptr.tellg()==0 && f3ptr.tellg()==0)
		{
			cout<<"\nError. No records to display.\n\n";
		}
		
		f1ptr.seekg(0,ios::beg);
		f2ptr.seekg(0,ios::beg);
		f3ptr.seekg(0,ios::beg);
		int count=0;
		int p1,anoc;
		char sr1[20],sr2[20];
		cout<<"\n**********PROPERTIES**********\n\n\n";
		cout<<"******PROPERTY TYPE******\n\n1. RESIDENTIAL\n2. COMMERCIAL\nEnter your choice: ";
		cin>>pchoice;
		while(pchoice<1 || pchoice>2)
		{
				cout<<"\nInvalid entry! Enter valid choice: ";
				cin>>pchoice;
		}
		if(pchoice==2)
		{
			commercial cm1,cm2;
			f3ptr.clear();
			f3ptr.seekg(0,ios::beg);
			f3ptr.read((char*)&cm1,sizeof(commercial));
			while(!f3ptr.eof())
			{
				if(cm1.available==1 && tolower(cm1.purchasetype)==tolower(cho))
				count++;
				f3ptr.read((char*)&cm1,sizeof(commercial));
			}
			if(count==0)
			{
				cout<<"\nNo available commercial properties to display.\nPress any key to continue...";
				f3ptr.close();
				f2ptr.close();
				f1ptr.close();
				getchar();
				return 0;
			}
			else
			{
				int index=0;
				f3ptr.clear();
				f3ptr.seekg(0,ios::beg);
				commercial comarr[count];
				f3ptr.read((char*)&cm1,sizeof(commercial));
				
				cout<<"\nSerial No. | Name | Size | Available | Shops | Facing Type | Purchase Type | Commercial Zone | Buy Price (Rs.)\n\n";
				while(!f3ptr.eof())
				{
					if(cm1.available==1 && tolower(cm1.purchasetype)==tolower(cho))
					{
					comarr[index]=cm1;
					index+=1;
					strcpy(sr1,"YES");
					
					if(cm1.get_shoplocation()=='i')
					strcpy(sr2,"Internal");
					else
					strcpy(sr2,"Front Facing");

					printf("\n%-10d %-10s %.2f %-10s %10d %-10s %10c %10s %.2f",index,cm1.pname,cm1.psize,sr1,cm1.get_shops(),sr2,toupper(cm1.purchasetype),cm1.get_zonename(),cm1.baserate);
					}//print statement
					f3ptr.read((char*)&cm1,sizeof(commercial));
				}
				f3ptr.clear();
				cout<<"\nEnter desired property number: ";
				cin>>cho1;
				while(!(cho1>=1 && cho1<=count))
				{
					cout<<"\nInvalid entry. Enter valid property number: ";
					cin>>cho1;
				}
				cho1-=1;
				
				cout<<"\nProperty details: \n";
				comarr[cho1].displaydetails();//
				
				cout<<"\nConfirm transaction. Enter 1 if yes, any other key to exit: ";
				cin>>anoc;
				if(anoc!=1)
				{
					f3ptr.close();
					f2ptr.close();
					f1ptr.close();
					cout<<"\nTransaction cancelled. Press any key to continue...";
					getchar();
					getchar();
					return 1;
				}
				else
				{
					if(this->budget!=-1){
					if(comarr[cho1].baserate>this->budget || comarr[cho1].monthrent>this->budget)
					{
						cout<<"\nError! Can not proceed since purchase price exceeds bugdet. Please set new budget, or disable it\n\n";
						f3ptr.close();
						f2ptr.close();
						f1ptr.close();
						cout<<"\nPress any key to continue...";
						getchar();
						getchar();
						return 1;
					}}
					
					agent agt;
					fstream agtptr;
					string fn="AgentInfo.dat";
					agtptr.open(fn.c_str(),ios::binary|ios::in|ios::out);
					agtptr.read((char*)&agt,sizeof(agent));
					while(!agtptr.eof())
					{
						if(comarr[cho1].get_sellerid()==agt.get_agentid())
						{
							break;
						}
						agtptr.read((char*)&agt,sizeof(agent));
					}
					if(tolower(cho)=='b')
					{
						Sleep(150);
						cout<<"\nUpdating Agent Information.\n";
						agt.income=agt.income+((comarr[cho1].baserate)*(agt.crate/100));
						agt.totalsales+=1;
						
						agtptr.seekp(-sizeof(agent),ios::cur);
						agtptr.write((char*)&agt,sizeof(agent));
						agtptr.close();
						cout<<"\nYou have been charged Rs. "<<comarr[cho1].baserate<<"  for BUYING property  "<<comarr[cho1].get_pname()<<"  by Agent "<<agt.get_fullname();
						Sleep(350);
						cout<<"\nContract for Property No. "<<comarr[cho1].propertyid<<" now available to be viewed in Property Dashboard.\n";
						Sleep(150);
						//update property
						cout<<"\nUpdating Property Information.\n";
						comarr[cho1].set_ownerid(this->custid);
						comarr[cho1].set_ownername(this->fullname);
						comarr[cho1].available=0;
						time_t now = time(0);
   						tm *ltm = localtime(&now);
   						comarr[cho1].purchasedate.d=ltm->tm_mday;
   						comarr[cho1].purchasedate.m=1+ltm->tm_mon;
						comarr[cho1].purchasedate.y=1900 + ltm->tm_year;
						
						f3ptr.clear();
						f3ptr.seekg(0,ios::beg);
						f3ptr.read((char*)&cm2,sizeof(commercial));
						while(!f3ptr.eof())
						{
							if(cm2.propertyid==comarr[cho1].propertyid)
							break;
							f3ptr.read((char*)&cm2,sizeof(commercial));
						}
						f3ptr.seekp(-sizeof(commercial),ios::cur);
						f3ptr.write((char*)&comarr[cho1],sizeof(commercial));//property written
						Sleep(150);
						cout<<"\nUpdating Customer Information\n";
						//update customer
						customer cum1;
						Sleep(150);
						string cumname="CustomerInfo.dat";
						fstream cumptr;
						cumptr.open(cumname.c_str(),ios::binary|ios::in|ios::out);
						cumptr.read((char*)&cum1,sizeof(customer));
						while(!cumptr.eof())
						{
							if(cum1.get_custid()==(this->custid))
							{
								break;
							}
							cumptr.read((char*)&cum1,sizeof(customer));
						}
						cum1.acctotal=cum1.acctotal+comarr[cho1].baserate;
						cum1.buytotal=cum1.buytotal+comarr[cho1].baserate;
						if(this->budget!=-1)
						{
						cum1.budget-=comarr[cho1].baserate;
						}
						cum1.totalprops++;
						
							Sleep(150);
						if(cum1.totalprops>=5 && cum1.totalprops<=10)
						{
							cout<<"\n\nDiscount received: 5%\nAmount saved: "<<0.05*comarr[cho1].baserate<<endl;
							cum1.acctotal=cum1.acctotal-(0.05*comarr[cho1].baserate);
							cum1.buytotal=cum1.buytotal-(0.05*comarr[cho1].baserate);
							cout<<"\nAccount information updated.\n\n";
						}
						else
						{
							cout<<"\n\nDiscount received: 10%\nAmount saved: "<<0.1*comarr[cho1].baserate<<endl;
							cum1.acctotal=cum1.acctotal-(0.1*comarr[cho1].baserate);
							cum1.buytotal=cum1.buytotal-(0.1*comarr[cho1].baserate);
							cout<<"\nAccount information updated.\n\n";
						}
						
						this->copyobj(cum1);
						cout<<"\nYou have been charged Rs. "<<comarr[cho1].baserate<<"  for BUYING property  "<<comarr[cho1].get_pname()<<"  by Agent "<<agt.get_fullname();
						Sleep(350);
						cout<<"\nContract for Property No. "<<comarr[cho1].propertyid<<" now available to be viewed in Property Dashboard.\n";
						Sleep(150);
						cumptr.seekp(-sizeof(customer),ios::cur);
						cumptr.write((char*)&cum1,sizeof(customer));
						cumptr.close();
					}
					else if(tolower(cho)=='r')
					{
						Sleep(150);
						cout<<"\nUpdating Agent Information.\n";
						agt.income=agt.income+((comarr[cho1].monthrent)*(agt.crate/100));
						agt.totalsales+=1;
						agt.rentcollected+=comarr[cho1].monthrent;
						
						agtptr.seekp(-sizeof(agent),ios::cur);
						agtptr.write((char*)&agt,sizeof(agent));
						agtptr.close();
						Sleep(150);
						cout<<"\nYou have been charged Rs. "<<comarr[cho1].monthrent<<"  for RENTING property  "<<comarr[cho1].get_pname()<<"  by Agent "<<agt.get_fullname()<<"\nAgent description: "<<agt.get_description();
					Sleep(150);
						cout<<"\nContract for Property No. "<<comarr[cho1].propertyid<<" now available to be viewed in Property Dashboard.\n";
						//update property
						Sleep(150);
						cout<<"\nUpdating Property Information.\n";
						comarr[cho1].set_ownerid(this->custid);
						comarr[cho1].set_ownername(this->fullname);
						comarr[cho1].available=0;
						comarr[cho1].propertyrent+=comarr[cho1].monthrent;
						time_t now = time(0);
   						tm *ltm = localtime(&now);
   						comarr[cho1].purchasedate.d=ltm->tm_mday;
   						comarr[cho1].purchasedate.m=1+ltm->tm_mon;
						comarr[cho1].purchasedate.y=1900 + ltm->tm_year;
						
						f3ptr.clear();
						f3ptr.seekg(0,ios::beg);
						f3ptr.read((char*)&cm2,sizeof(commercial));
						while(!f3ptr.eof())
						{
							if(cm2.propertyid==comarr[cho1].propertyid)
							break;
							f3ptr.read((char*)&cm2,sizeof(commercial));
						}
						f3ptr.seekp(-sizeof(commercial),ios::cur);
						f3ptr.write((char*)&comarr[cho1],sizeof(commercial));//property written
						Sleep(150);
						cout<<"\nUpdating Customer Information\n";
						//update customer
						customer cum1;
						string cumname="CustomerInfo.dat";
						fstream cumptr;
						cumptr.open(cumname.c_str(),ios::binary|ios::in|ios::out);
						cumptr.read((char*)&cum1,sizeof(customer));
						while(!cumptr.eof())
						{
							if(cum1.get_custid()==(this->custid))
							{
								break;
							}
							cumptr.read((char*)&cum1,sizeof(customer));
						}
						cum1.acctotal=cum1.acctotal+comarr[cho1].monthrent;
						cum1.renttotal=cum1.renttotal+comarr[cho1].monthrent;
						if(this->budget!=-1)
						{
						cum1.budget-=comarr[cho1].monthrent;
						}
						cum1.totalprops++;
						
						Sleep(150);
						if(cum1.totalprops>=5 && cum1.totalprops<=10)
						{
							cout<<"\n\nDiscount received: 5%\nAmount saved: "<<0.05*comarr[cho1].monthrent<<endl;
							cum1.acctotal=cum1.acctotal-(0.05*comarr[cho1].monthrent);
							cum1.renttotal=cum1.renttotal-(0.05*comarr[cho1].monthrent);
							cout<<"\nAccount information updated.\n\n";
						}
						else
						{
							cout<<"\n\nDiscount received: 10%\nAmount saved: "<<0.1*comarr[cho1].monthrent<<endl;
							cum1.acctotal=cum1.acctotal-(0.1*comarr[cho1].monthrent);
							cum1.renttotal=cum1.renttotal-(0.1*comarr[cho1].monthrent);
							cout<<"\nAccount information updated.\n\n";
						}
						
						Sleep(150);
						this->copyobj(cum1);
						cout<<"\n\nCustomer Information Updated.\n\n";
						Sleep(300);
						cout<<"\nYou have been charged Rs. "<<comarr[cho1].monthrent<<"  for RENTING property  "<<comarr[cho1].get_pname()<<"  by Agent "<<agt.get_fullname()<<"\nAgent description: "<<agt.get_description();
						Sleep(150);
						cout<<"\nContract for Property No. "<<comarr[cho1].propertyid<<" now available to be viewed in Property Dashboard.\n";
						
						cumptr.seekp(-sizeof(customer),ios::cur);
						cumptr.write((char*)&cum1,sizeof(customer));
						cumptr.close();
					}
				}
			}
		}
		else if(pchoice==1)
		{
			int rc;//hosues and flats
			cout<<"\nEnter: \n1. For Houses\n2. For Flats: ";
			cin>>rc;
			while(rc!=1 && rc!=2)
			{
				cout<<"\nInvalid entry. Enter: \n1. For Houses\n2. For Flats: ";
				cin>>rc;
			}
			if(rc==1)
			{
				house cm1,cm2;
			f1ptr.clear();
			f1ptr.seekg(0,ios::beg);
			f1ptr.read((char*)&cm1,sizeof(house));
			while(!f1ptr.eof())
			{
				if(cm1.available==1 && tolower(cm1.purchasetype)==tolower(cho))
				count++;
				f1ptr.read((char*)&cm1,sizeof(house));
			}
			if(count==0)
			{
				Sleep(300);
				cout<<"\nNo available residential properties to display.\nPress any key to continue...";
				f3ptr.close();
				f2ptr.close();
				f1ptr.close();
				getchar();
				getchar();
				return 0;
			}
			else
			{
				int index=0;
				f1ptr.clear();
				f1ptr.seekg(0,ios::beg);
				house comarr[count];
				cout<<"\nSerial No. | Name | Size (Sq. Guz) | Available | Rooms | House Type | Purchase Type |  Floors | Furnished | Buy Price (Rs.)\n";
				f1ptr.read((char*)&cm1,sizeof(house));
				while(!f1ptr.eof())
				{
					if(cm1.available==1 && tolower(cm1.purchasetype)==tolower(cho))
					{
						Sleep(200);
						comarr[index]=cm1;
						index+=1;
						if(cm1.available==1)
						strcpy(sr1,"YES");
						else
						strcpy(sr1,"NO");
						if(cm1.furnished==1)
						strcpy(sr2,"YES");
						else
						strcpy(sr2,"NO");
						
						printf("\n%-10d %-10s %.2f %-10s %10d %-10s %10c %10d %-10s %.2f",index,cm1.pname,cm1.psize,sr1,cm1.rooms,cm1.get_housetype(),toupper(cm1.purchasetype),cm1.floors,sr2,cm1.baserate);//co1.pname<<co1.psize<<sr1<<co1.get_shops()<<toupper(co1.purchasetype)<<co1.get_zonename()<<co1.baserate;
					}
					f1ptr.read((char*)&cm1,sizeof(house));
				}
				f1ptr.clear();
				Sleep(150);
				cout<<"\nEnter desired property number: ";
				cin>>cho1;
				while(!(cho1>=1 && cho1<=count))
				{
					cout<<"\nInvalid entry. Enter valid property number: ";
					cin>>cho1;
				}
				cho1-=1;
				
				cout<<"\nProperty details: \n";
				Sleep(400);
				comarr[cho1].displaydetails();
				Sleep(300);				
				cout<<"\nConfirm transaction. Enter 1 if yes, any other key to exit: ";
				cin>>anoc;
				if(anoc!=1)
				{
					f3ptr.close();
					f2ptr.close();
					f1ptr.close();
					cout<<"\nPress any key to continue...";
					getchar();
					getchar();
					return 1;
				}
				else
				{
					if(this->budget!=-1)
					{
						if(comarr[cho1].baserate>this->budget || comarr[cho1].monthrent>this->budget)
						{
							cout<<"\nError! Can not proceed since purchase price exceeds bugdet. Please set new budget, or disable it\n\n";
							f3ptr.close();
							f2ptr.close();
							f1ptr.close();
							cout<<"\nPress any key to continue...";
							getchar();
							getchar();
							return 1;
						}
					}
					agent agt;
					fstream agtptr;
					string fn="AgentInfo.dat";
					agtptr.open(fn.c_str(),ios::binary|ios::in|ios::out);
					agtptr.read((char*)&agt,sizeof(agent));
					while(!agtptr.eof())
					{
						if(comarr[cho1].get_sellerid()==agt.get_agentid())
						{
							break;
						}
						agtptr.read((char*)&agt,sizeof(agent));
					}
					Sleep(250);
					if(tolower(cho)=='b')
					{
						cout<<"\nUpdating Agent Information.\n";
						agt.income=agt.income+((comarr[cho1].baserate)*(agt.crate/100));
						agt.totalsales+=1;
						
						agtptr.seekp(-sizeof(agent),ios::cur);
						agtptr.write((char*)&agt,sizeof(agent));
						agtptr.close();
						//cout<<"\nYou have been charged Rs. "<<comarr[cho1].baserate<<"  for purchasing property  "<<comarr[cho1].get_pname()<<"  by Agent "<<agt.get_fullname();
						//cout<<"\nContract for Property No. "<<comarr[cho1].propertyid<<" now available to be viewed in Property Dashboard.\n";
						//update property
						Sleep(150);
						cout<<"\nUpdating Property Information.\n";
						comarr[cho1].set_ownerid(this->custid);
						comarr[cho1].set_ownername(this->fullname);
						comarr[cho1].available=0;
						time_t now = time(0);
   						tm *ltm = localtime(&now);
   						comarr[cho1].purchasedate.d=ltm->tm_mday;
   						comarr[cho1].purchasedate.m=1+ltm->tm_mon;
						comarr[cho1].purchasedate.y=1900 + ltm->tm_year;
						
						f1ptr.clear();
						f1ptr.seekg(0,ios::beg);
						f1ptr.read((char*)&cm2,sizeof(house));
						while(!f1ptr.eof())
						{
							if(cm2.propertyid==comarr[cho1].propertyid)
							break;
							f1ptr.read((char*)&cm2,sizeof(house));
						}
						f1ptr.seekp(-sizeof(house),ios::cur);
						f1ptr.write((char*)&comarr[cho1],sizeof(house));//property written
						
						//update customer
						Sleep(150);
						cout<<"\nUpdating Customer Information\n";
						customer cum1;
						string cumname="CustomerInfo.dat";
						fstream cumptr;
						cumptr.open(cumname.c_str(),ios::binary|ios::in|ios::out);
						cumptr.read((char*)&cum1,sizeof(customer));
						while(!cumptr.eof())
						{
							if(cum1.get_custid()==(this->custid))
							{
								break;
							}
							cumptr.read((char*)&cum1,sizeof(customer));
						}
						cum1.acctotal=cum1.acctotal+comarr[cho1].baserate;
						cum1.buytotal=cum1.buytotal+comarr[cho1].baserate;
						if(this->budget!=-1)
						{
						cum1.budget-=comarr[cho1].baserate;
						}
						cum1.totalprops++;
						
						Sleep(150);
						if(cum1.totalprops>=5 && cum1.totalprops<=10)
						{
							Sleep(150);
							cout<<"\n\nDiscount received: 5%\nAmount saved: "<<0.05*comarr[cho1].baserate<<endl;
							cum1.acctotal=cum1.acctotal-(0.05*comarr[cho1].baserate);
							cum1.buytotal=cum1.buytotal-(0.05*comarr[cho1].baserate);
							cout<<"\nAccount information updated.\n\n";
						}
						else
						{
							Sleep(150);
							cout<<"\n\nDiscount received: 10%\nAmount saved: "<<0.1*comarr[cho1].baserate<<endl;
							cum1.acctotal=cum1.acctotal-(0.1*comarr[cho1].baserate);
							cum1.buytotal=cum1.buytotal-(0.1*comarr[cho1].baserate);
							cout<<"\nAccount information updated.\n\n";
						}
						
						Sleep(150);
						if(comarr[cho1].furnished!=1)
						{
							cout<<"\n\nProperty currently furnished. Do you wish to add furnish charges to purchase?: ";
							cin>>fchoice;
							while(tolower(fchoice)!='n' && tolower(fchoice)!='y')
							{
								cout<<"\nInvalid choice entered. Enter valid choice: ";
								cin>>fchoice;
							}
							Sleep(150);
							if(tolower(fchoice)=='y')
							{
								cout<<"\nYou have been successfully charged   Rs. "<<comarr[cho1].furnishcharge<<"  in furnish charges.\n";
								cum1.acctotal=cum1.acctotal+comarr[cho1].furnishcharge;
							}
						}
						else
						{
							Sleep(150);
							cout<<"\nProperty FURNISHED.\nFurnish Cost:   Rs. "<<comarr[cho1].furnishcost<<"   included in transaction.\n";
						}
						
						Sleep(300);
						cout<<"\nYou have been charged Rs. "<<comarr[cho1].baserate<<"  for purchasing property  "<<comarr[cho1].get_pname()<<"  by Agent "<<agt.get_fullname();
						Sleep(150);
						cout<<"\nContract for Property No. "<<comarr[cho1].propertyid<<" now available to be viewed in Property Dashboard.\n";
					
						this->copyobj(cum1);
						cumptr.seekp(-sizeof(customer),ios::cur);
						cumptr.write((char*)&cum1,sizeof(customer));
						cumptr.close();
					}
					else if(tolower(cho)=='r')
					{
						cout<<"\nUpdating Agent Information.\n";
						agt.income=agt.income+((comarr[cho1].monthrent)*(agt.crate/100));
						agt.totalsales+=1;
						agt.rentcollected+=comarr[cho1].monthrent;
						
						agtptr.seekp(-sizeof(agent),ios::cur);
						agtptr.write((char*)&agt,sizeof(agent));
						agtptr.close();
						//cout<<"\nYou have been charged Rs. "<<comarr[cho1].monthrent<<"  for renting property  "<<comarr[cho1].get_pname()<<"  by Agent "<<agt.get_fullname()<<"\nAgent description: "<<agt.get_description();
						//cout<<"\nContract for Property No. "<<comarr[cho1].propertyid<<" now available to be viewed in Property Dashboard.\n";
						//update property
						cout<<"\nUpdating Property Information.\n";
						comarr[cho1].set_ownerid(this->custid);
						comarr[cho1].set_ownername(this->fullname);
						comarr[cho1].available=0;
						comarr[cho1].propertyrent+=comarr[cho1].monthrent;
						time_t now = time(0);
   						tm *ltm = localtime(&now);
   						comarr[cho1].purchasedate.d=ltm->tm_mday;
   						comarr[cho1].purchasedate.m=1+ltm->tm_mon;
						comarr[cho1].purchasedate.y=1900 + ltm->tm_year;
						
						f1ptr.clear();
						f1ptr.seekg(0,ios::beg);
						f1ptr.read((char*)&cm2,sizeof(house));
						while(!f1ptr.eof())
						{
							if(cm2.propertyid==comarr[cho1].propertyid)
							break;
							f1ptr.read((char*)&cm2,sizeof(house));
						}
						f1ptr.seekp(-sizeof(house),ios::cur);
						f1ptr.write((char*)&comarr[cho1],sizeof(house));//property written
						
						//update customer
						customer cum1;
						cout<<"\nUpdating Customer Information\n";
						string cumname="CustomerInfo.dat";
						fstream cumptr;
						cumptr.open(cumname.c_str(),ios::binary|ios::in|ios::out);
						cumptr.read((char*)&cum1,sizeof(customer));
						while(!cumptr.eof())
						{
							if(cum1.get_custid()==(this->custid))
							{
								break;
							}
							cumptr.read((char*)&cum1,sizeof(customer));
						}
						cum1.acctotal=cum1.acctotal+comarr[cho1].monthrent;
						cum1.renttotal=cum1.renttotal+comarr[cho1].monthrent;
						if(this->budget!=-1)
						{
						cum1.budget-=comarr[cho1].monthrent;
						}
						cum1.totalprops++;
							Sleep(150);
						if(cum1.totalprops>=5 && cum1.totalprops<=10)
						{
							Sleep(150);
							cout<<"\n\nDiscount received: 5%\nAmount saved: "<<0.05*comarr[cho1].monthrent<<endl;
							cum1.acctotal=cum1.acctotal-(0.05*comarr[cho1].monthrent);
							cum1.renttotal=cum1.renttotal-(0.05*comarr[cho1].monthrent);
							cout<<"\nAccount information updated.\n\n";
						}
						else
						{
							Sleep(150);
							cout<<"\n\nDiscount received: 10%\nAmount saved: "<<0.1*comarr[cho1].monthrent<<endl;
							cum1.acctotal=cum1.acctotal-(0.1*comarr[cho1].monthrent);
							cum1.renttotal=cum1.renttotal-(0.1*comarr[cho1].monthrent);
							cout<<"\nAccount information updated.\n\n";
						}
						
						Sleep(150);
						if(comarr[cho1].furnished!=1)
						{
							cout<<"\n\nProperty currently furnished. Do you wish to add furnish charges to purchase?: ";
							cin>>fchoice;
							while(tolower(fchoice)!='n' && tolower(fchoice)!='y')
							{
								cout<<"\nInvalid choice entered. Enter valid choice: ";
								cin>>fchoice;
							}
							Sleep(150);
							if(tolower(fchoice)=='y')
							{
								cout<<"\nYou have been successfully charged   Rs. "<<comarr[cho1].furnishcharge<<"  in furnish charges.\nAccount total updated.\n";
								cum1.acctotal=cum1.acctotal+comarr[cho1].furnishcharge;
							}
						}
						else
						{
							Sleep(150);
							cout<<"\nProperty FURNISHED.\nFurnish Cost:   Rs. "<<comarr[cho1].furnishcost<<"   included in transaction.\n";
						}
						
						Sleep(300);
						cout<<"\nYou have been charged Rs. "<<comarr[cho1].baserate<<"  for purchasing property  "<<comarr[cho1].get_pname()<<"  by Agent "<<agt.get_fullname();
						cout<<"\nContract for Property No. "<<comarr[cho1].propertyid<<" now available to be viewed in Property Dashboard.\n";
					
						this->copyobj(cum1);
						cumptr.seekp(-sizeof(customer),ios::cur);
						cumptr.write((char*)&cum1,sizeof(customer));
						cumptr.close();
					}
				}
			}
			}
			else
			{
				flat cm1,cm2;
				f2ptr.clear();
				f2ptr.seekg(0,ios::beg);
				f2ptr.read((char*)&cm1,sizeof(flat));
			while(!f2ptr.eof())
			{
				if(cm1.available==1 && tolower(cm1.purchasetype)==tolower(cho))
				count++;
				f2ptr.read((char*)&cm1,sizeof(flat));
			}
			if(count==0)
			{
				cout<<"\nNo available residential properties to display.\nPress any key to continue...";
				f3ptr.close();
				f2ptr.close();
				f1ptr.close();
				getchar();
				getchar();
				return 0;
			}
			else
			{
				int index=0;
				char sr3[50],sr4[50];
				f2ptr.clear();
				f2ptr.seekg(0,ios::beg);
				flat comarr[count];
				f2ptr.read((char*)&cm1,sizeof(flat));
				cout<<"\nSerial No. | Name | Size (Sq. Guz) | Available | Rooms | Parking | Purchase Type |  Elevator | Furnished | Buy Price (Rs.)\n";
				while(!f2ptr.eof())
				{
					if(cm1.available==1 && tolower(cm1.purchasetype)==tolower(cho))
					{
						Sleep(200);
						comarr[index]=cm1;
						index+=1;
						if(cm1.available==1)
						strcpy(sr1,"YES");
						else
						strcpy(sr1,"NO");
						if(cm1.furnished==1)
						strcpy(sr2,"YES");
						else
						strcpy(sr2,"NO");
						if(cm1.get_parking()==1)
						strcpy(sr3,"YES");
						else
						strcpy(sr3,"NO");
						if(cm1.get_elevator()==1)
						strcpy(sr4,"YES");
						else
						strcpy(sr4,"NO");
						
						printf("\n%-10d %-10s %.2f %-10s %10d %-10s %10c %-10s %-10s %.2f",index,cm1.pname,cm1.psize,sr1,cm1.rooms,sr3,toupper(cm1.purchasetype),sr4,sr2,cm1.baserate);
					}
					f2ptr.read((char*)&cm1,sizeof(flat));
				}
				f2ptr.clear();
				cout<<"\nEnter desired property number: ";
				cin>>cho1;
				while(!(cho1>=1 && cho1<=count))
				{
					cout<<"\nInvalid entry. Enter valid property number: ";
					cin>>cho1;
				}
				cho1-=1;
				Sleep(350);
				cout<<"\nProperty details: \n";
				comarr[cho1].displaydetails();
				Sleep(250);
				cout<<"\nConfirm transaction. Enter 1 if yes, any other key to exit: ";
				cin>>anoc;
				if(anoc!=1)
				{
					f3ptr.close();
					f2ptr.close();
					f1ptr.close();
					cout<<"\nPress any key to continue...";
					getchar();
					getchar();
					return 1;
				}
				else
				{
					if(this->budget!=-1)
					{
						if(comarr[cho1].baserate>this->budget || comarr[cho1].monthrent>this->budget)
						{
							cout<<"\nError! Can not proceed since purchase price exceeds bugdet. Please set new budget, or disable it\n\n";
							f3ptr.close();
							f2ptr.close();
							f1ptr.close();
							cout<<"\nPress any key to continue...";
							getchar();
							getchar();
							return 1;
						}
					}
					
					agent agt;
					fstream agtptr;
					string fn="AgentInfo.dat";
					agtptr.open(fn.c_str(),ios::binary|ios::in|ios::out);
					agtptr.read((char*)&agt,sizeof(agent));
					while(!agtptr.eof())
					{
						if(comarr[cho1].get_sellerid()==agt.get_agentid())
						{
							break;
						}
						agtptr.read((char*)&agt,sizeof(agent));
					}
					Sleep(300);
					if(tolower(cho)=='b')
					{
						cout<<"\nUpdating Agent Information.\n";
						agt.income=agt.income+((comarr[cho1].baserate)*(agt.crate/100));
						agt.totalsales+=1;
						
						agtptr.seekp(-sizeof(agent),ios::cur);
						agtptr.write((char*)&agt,sizeof(agent));
						agtptr.close();
						//cout<<"\nYou have been charged Rs. "<<comarr[cho1].baserate<<"  for purchasing property  "<<comarr[cho1].get_pname()<<"  by Agent "<<agt.get_fullname();
						//cout<<"\nContract for Property No. "<<comarr[cho1].propertyid<<" now available to be viewed in Property Dashboard.\n";
						//update property
						Sleep(250);
						cout<<"\nUpdating Property Information.\n";
						comarr[cho1].set_ownerid(this->custid);
						comarr[cho1].set_ownername(this->fullname);
						comarr[cho1].available=0;
						time_t now = time(0);
   						tm *ltm = localtime(&now);
   						comarr[cho1].purchasedate.d=ltm->tm_mday;
   						comarr[cho1].purchasedate.m=1+ltm->tm_mon;
						comarr[cho1].purchasedate.y=1900 + ltm->tm_year;
						
						f2ptr.clear();
						f2ptr.seekg(0,ios::beg);
						f2ptr.read((char*)&cm2,sizeof(flat));
						while(!f2ptr.eof())
						{
							if(cm2.propertyid==comarr[cho1].propertyid)
							break;
							f2ptr.read((char*)&cm2,sizeof(flat));
						}
						f2ptr.seekp(-sizeof(flat),ios::cur);
						f2ptr.write((char*)&comarr[cho1],sizeof(flat));//property written
						
						//update customer
						Sleep(300);
						cout<<"\nUpdating Customer Information\n";
						customer cum1;
						string cumname="CustomerInfo.dat";
						fstream cumptr;
						cumptr.open(cumname.c_str(),ios::binary|ios::in|ios::out);
						cumptr.read((char*)&cum1,sizeof(customer));
						while(!cumptr.eof())
						{
							if(cum1.get_custid()==(this->custid))
							{
								break;
							}
							cumptr.read((char*)&cum1,sizeof(customer));
						}
						cum1.acctotal=cum1.acctotal+comarr[cho1].baserate;
						cum1.buytotal=cum1.buytotal+comarr[cho1].baserate;
						if(this->budget!=-1)
						{
						cum1.budget-=comarr[cho1].baserate;
						}
						cum1.totalprops++;
						
							Sleep(150);
						if(cum1.totalprops>=5 && cum1.totalprops<=10)
						{
							Sleep(150);
							cout<<"\n\nDiscount received: 5%\nAmount saved: "<<0.05*comarr[cho1].baserate<<endl;
							cum1.acctotal=cum1.acctotal-(0.05*comarr[cho1].baserate);
							cum1.buytotal=cum1.buytotal-(0.05*comarr[cho1].baserate);
							cout<<"\nAccount information updated.\n\n";
						}
						else
						{
							Sleep(150);
							cout<<"\n\nDiscount received: 10%\nAmount saved: "<<0.1*comarr[cho1].baserate<<endl;
							cum1.acctotal=cum1.acctotal-(0.1*comarr[cho1].baserate);
							cum1.buytotal=cum1.buytotal-(0.1*comarr[cho1].baserate);
							cout<<"\nAccount information updated.\n\n";
						}
						
						Sleep(150);
						if(comarr[cho1].furnished!=1)
						{
							cout<<"\n\nProperty currently furnished. Do you wish to add furnish charges to purchase?: ";
							cin>>fchoice;
							while(tolower(fchoice)!='n' && tolower(fchoice)!='y')
							{
								cout<<"\nInvalid choice entered. Enter valid choice: ";
								cin>>fchoice;
							}
							Sleep(150);
							if(tolower(fchoice)=='y')
							{
								cout<<"\nYou have been successfully charged   Rs. "<<comarr[cho1].furnishcharge<<"  in furnish charges.\n";
								cum1.acctotal=cum1.acctotal+comarr[cho1].furnishcharge;
								cum1.buytotal=cum1.buytotal+comarr[cho1].furnishcharge;
							}
						}
						else
						{
							Sleep(150);
							cout<<"\nProperty FURNISHED.\nFurnish Cost:   Rs. "<<comarr[cho1].furnishcost<<"   included in transaction.\n";
						}
						
						Sleep(300);
						cout<<"\nYou have been charged Rs. "<<comarr[cho1].baserate<<"  for purchasing property  "<<comarr[cho1].get_pname()<<"  by Agent "<<agt.get_fullname();
						Sleep(150);
						cout<<"\nContract for Property No. "<<comarr[cho1].propertyid<<" now available to be viewed in Property Dashboard.\n";
					
						this->copyobj(cum1);
						cumptr.seekp(-sizeof(customer),ios::cur);
						cumptr.write((char*)&cum1,sizeof(customer));
						cumptr.close();
					}
					else if(tolower(cho)=='r')
					{
						cout<<"\nUpdating Agent Information.\n";
						agt.income=agt.income+((comarr[cho1].monthrent)*(agt.crate/100));
						agt.totalsales+=1;
						agt.rentcollected+=comarr[cho1].monthrent;
						
						agtptr.seekp(-sizeof(agent),ios::cur);
						agtptr.write((char*)&agt,sizeof(agent));
						agtptr.close();
						//cout<<"\nYou have been charged Rs. "<<comarr[cho1].monthrent<<"  for renting property  "<<comarr[cho1].get_pname()<<"  by Agent "<<agt.get_fullname()<<"\nAgent description: "<<agt.get_description();
						//cout<<"\nContract for Property No. "<<comarr[cho1].propertyid<<" now available to be viewed in Property Dashboard.\n";
						//update property
						cout<<"\nUpdating Property Information.\n";
						comarr[cho1].set_ownerid(this->custid);
						comarr[cho1].set_ownername(this->fullname);
						comarr[cho1].available=0;
						comarr[cho1].propertyrent+=comarr[cho1].monthrent;
						time_t now = time(0);
   						tm *ltm = localtime(&now);
   						comarr[cho1].purchasedate.d=ltm->tm_mday;
   						comarr[cho1].purchasedate.m=1+ltm->tm_mon;
						comarr[cho1].purchasedate.y=1900 + ltm->tm_year;
						
						f2ptr.clear();
						f2ptr.seekg(0,ios::beg);
						f2ptr.read((char*)&cm2,sizeof(flat));
						while(!f2ptr.eof())
						{
							if(cm2.propertyid==comarr[cho1].propertyid)
							break;
							f2ptr.read((char*)&cm2,sizeof(flat));
						}
						f2ptr.seekp(-sizeof(flat),ios::cur);
						f2ptr.write((char*)&comarr[cho1],sizeof(flat));//property written
						
						//update customer
							cout<<"\nUpdating Customer Information\n";
						customer cum1;
						string cumname="CustomerInfo.dat";
						fstream cumptr;
						cumptr.open(cumname.c_str(),ios::binary|ios::in|ios::out);
						cumptr.read((char*)&cum1,sizeof(customer));
						while(!cumptr.eof())
						{
							if(cum1.get_custid()==(this->custid))
							{
								break;
							}
							cumptr.read((char*)&cum1,sizeof(customer));
						}
						cum1.acctotal=cum1.acctotal+comarr[cho1].monthrent;
						cum1.renttotal=cum1.renttotal+comarr[cho1].monthrent;
						if(this->budget!=-1)
						{
						cum1.budget-=comarr[cho1].monthrent;
						}
						cum1.totalprops++;
						
							Sleep(150);
						if(cum1.totalprops>=5 && cum1.totalprops<=10)
						{
							Sleep(150);
							cout<<"\n\nDiscount received: 5%\nAmount saved: "<<0.05*comarr[cho1].monthrent<<endl;
							cum1.acctotal=cum1.acctotal-(0.05*comarr[cho1].monthrent);
							cum1.renttotal=cum1.renttotal-(0.05*comarr[cho1].monthrent);
							cout<<"\nAccount information updated.\n\n";
						}
						else
						{
							Sleep(150);
							cout<<"\n\nDiscount received: 10%\nAmount saved: "<<0.1*comarr[cho1].monthrent<<endl;
							cum1.acctotal=cum1.acctotal-(0.1*comarr[cho1].monthrent);
							cum1.renttotal=cum1.renttotal-(0.1*comarr[cho1].monthrent);
							cout<<"\nAccount information updated.\n\n";
						}
						
						Sleep(150);
						if(comarr[cho1].furnished!=1)
						{
							cout<<"\n\nProperty currently furnished. Do you wish to add furnish charges to purchase?: ";
							cin>>fchoice;
							while(tolower(fchoice)!='n' && tolower(fchoice)!='y')
							{
								cout<<"\nInvalid choice entered. Enter valid choice: ";
								cin>>fchoice;
							}
							Sleep(150);
							if(tolower(fchoice)=='y')
							{
								cout<<"\nYou have been successfully charged   Rs. "<<comarr[cho1].furnishcharge<<"  in furnish charges.\n";
								cum1.acctotal=cum1.acctotal+comarr[cho1].furnishcharge;
							}
						}
						else
						{
							Sleep(150);
							cout<<"\nProperty FURNISHED.\nFurnish Cost:   Rs. "<<comarr[cho1].furnishcost<<"   included in transaction.\n";
						}
						
						Sleep(300);
						cout<<"\nYou have been charged Rs. "<<comarr[cho1].baserate<<"  for purchasing property  "<<comarr[cho1].get_pname()<<"  by Agent "<<agt.get_fullname();
						Sleep(150);
						cout<<"\nContract for Property No. "<<comarr[cho1].propertyid<<" now available to be viewed in Property Dashboard.\n";
					
						this->copyobj(cum1);
						cumptr.seekp(-sizeof(customer),ios::cur);
						cumptr.write((char*)&cum1,sizeof(customer));
						cumptr.close();
					}
				}
			
			}	
			}//
		}
		f3ptr.close();
		f2ptr.close();
		f1ptr.close();
		cout<<"\n\nPress any key to continue...";
		getchar();
		getchar();
		
	}
	
	void rent_property();
	//change property status from rented to bought ('r' to 'b')
	//charges the user the amount remaining on contract
	//if rent is paid in full already, do not charge further
	//else charge remaining amount and update customer, agent, and property objects accordingly 
	int rent_to_buy()
	{
		cout<<"\nNow showing rented properties...\n\n";
		int pchoice,cho1;
		fstream f1ptr,f2ptr,f3ptr;
		string str1="House.dat";
		string str2="Flats.dat";
		string str3="Commercial.dat";
		
		f1ptr.open(str1.c_str(),ios::binary|ios::in|ios::out);
		f2ptr.open(str2.c_str(),ios::binary|ios::in|ios::out);
		f3ptr.open(str3.c_str(),ios::binary|ios::in|ios::out);
		f1ptr.seekg(0,ios::end);
		f2ptr.seekg(0,ios::end);
		f3ptr.seekg(0,ios::end);
		
		if(!f1ptr || !f2ptr || !f3ptr)
		{
			cout<<"\nError opening files.\n";
			exit(1);
		}
		
		if(f1ptr.tellg()==0 && f2ptr.tellg()==0 && f3ptr.tellg()==0)
		{
			cout<<"\nError. No records to display.\n\n";
		}
		
		f1ptr.seekg(0,ios::beg);
		f2ptr.seekg(0,ios::beg);
		f3ptr.seekg(0,ios::beg);
		int count=0;
		int p1;
		char sr1[20],sr2[20];
		cout<<"\n**********PROPERTIES**********\n\n\n";
		cout<<"******PROPERTY TYPE******\n\n1. RESIDENTIAL\n2. COMMERCIAL\nEnter your choice: ";
		cin>>pchoice;
		while(pchoice<1 || pchoice>2)
		{
				cout<<"\nInvalid entry! Enter valid choice: ";
				cin>>pchoice;
		}
		if(pchoice==2)
		{
			commercial cm1,cm2;
			f3ptr.clear();
			f3ptr.read((char*)&cm1,sizeof(commercial));
			while(!f3ptr.eof())
			{
				if(tolower(cm1.purchasetype)=='r' && this->custid==cm1.ownerid)
				count++;
				f3ptr.read((char*)&cm1,sizeof(commercial));
			}
			if(count==0)
			{
				cout<<"\nNo available commercial properties to display.\nPress any key to continue...";
				f3ptr.close();
				f2ptr.close();
				f1ptr.close();
				getchar();
				getchar();
				return 1;
				
			}
			else
			{
				int index=0;
				f3ptr.clear();
				f3ptr.seekg(0,ios::beg);
				commercial comarr[count];
				f3ptr.read((char*)&cm1,sizeof(commercial));
				
				cout<<"\nSerial No. | Name | Size | Available | Shops | Facing Type | Purchase Type | Commercial Zone | Buy Price (Rs.)\n";
				while(!f3ptr.eof())
				{
					if(tolower(cm1.purchasetype)=='r' && this->custid==cm1.ownerid)
					{
					comarr[index]=cm1;
					index+=1;
					strcpy(sr1,"YES");
					
					if(cm1.get_shoplocation()=='i')
					strcpy(sr2,"Internal");
					else
					strcpy(sr2,"Front Facing");

					printf("\n%-10d %-10s %.2f %-10s %10d %-10s %10c %10s %.2f",index,cm1.pname,cm1.psize,sr1,cm1.get_shops(),sr2,toupper(cm1.purchasetype),cm1.get_zonename(),cm1.baserate);
					}//print statement
					f3ptr.read((char*)&cm1,sizeof(commercial));
				}
				f3ptr.clear();
				cout<<"\n\nEnter desired property number: ";
				cin>>cho1;
				while(!(cho1>=1 && cho1<=count))
				{
					cout<<"\nInvalid entry. Enter valid property number: ";
					cin>>cho1;
				}
				cho1-=1;
				
				cout<<"\n\nProperty details: \n";
				comarr[cho1].displaydetails();
				cout<<"\n\nNow updating purchase type: \n";
				cout<<"\n*Existing rent history will be removed\n*The amount remaining from contract will be now charged from your account\n\n";
				if(comarr[cho1].propertyrent<comarr[cho1].baserate)
				{
					//updating customer
					customer testc;
					fstream testptr;
					string tname="CustomerInfo.dat";
					testptr.open(tname.c_str(),ios::in|ios::out|ios::binary);
					testptr.read((char*)&testc,sizeof(customer));
					while(!testptr.eof())
					{
						if(testc.custid==this->custid)
						{
							break;
						}
						testptr.read((char*)&testc,sizeof(customer));
					}
					cout<<"\n\nRemaining dues: Rs. "<<comarr[cho1].baserate-comarr[cho1].propertyrent<<endl<<endl;
					testc.acctotal+=comarr[cho1].baserate-comarr[cho1].propertyrent;
					testc.buytotal+=comarr[cho1].baserate-comarr[cho1].propertyrent;
					testc.renttotal-=comarr[cho1].propertyrent;
					copyobj(testc);
					testptr.seekp(-sizeof(customer),ios::cur);
					testptr.write((char*)&testc,sizeof(customer));
					testptr.close();
					//updating property
					comarr[cho1].propertyrent=0;
					comarr[cho1].purchasetype='b';
					f3ptr.clear();	
					f3ptr.seekg(0,ios::beg);
					f3ptr.read((char*)&cm1,sizeof(commercial));
					while(!f3ptr.eof())
					{
						if(cm1.ownerid==this->custid && cm1.propertyid==comarr[cho1].propertyid)
						break;
						f3ptr.read((char*)&cm1,sizeof(commercial));
					}
					f3ptr.seekp(-sizeof(commercial),ios::cur);
					f3ptr.write((char*)&comarr[cho1],sizeof(commercial));
					//updating agent
					agent agt;
					fstream agtptr;
					string fn="AgentInfo.dat";
					agtptr.open(fn.c_str(),ios::binary|ios::in|ios::out);
					agtptr.read((char*)&agt,sizeof(agent));
					while(!agtptr.eof())
					{
						if(comarr[cho1].get_sellerid()==agt.get_agentid())
						{
							break;
						}
						agtptr.read((char*)&agt,sizeof(agent));
					}
			
					agt.income=agt.income+((comarr[cho1].baserate-comarr[cho1].propertyrent)*(agt.crate/100));	
					agtptr.seekp(-sizeof(agent),ios::cur);
					agtptr.write((char*)&agt,sizeof(agent));
					agtptr.close();
				}
				else
				{
					//updating property
					comarr[cho1].propertyrent=0;
					comarr[cho1].purchasetype='b';
					f3ptr.clear();	
					f3ptr.seekg(0,ios::beg);
					f3ptr.read((char*)&cm1,sizeof(commercial));
					while(!f3ptr.eof())
					{
						if(cm1.ownerid==this->custid && cm1.propertyid==comarr[cho1].propertyid)
						break;
						f3ptr.read((char*)&cm1,sizeof(commercial));
					}
					f3ptr.seekp(-sizeof(commercial),ios::cur);
					f3ptr.write((char*)&comarr[cho1],sizeof(commercial));
					cout<<"\nRent has already been collected in full.\n";	
				}
				cout<<"\nProperty status successfully updated from rent to buy. Press any key to continue...";
				getchar();
			}
		}
		else if(pchoice==1)
		{
			int rc;//hosues and flats
			cout<<"\nEnter: \n1. For Houses\n2. For Flats: ";
			cin>>rc;
			while(rc!=1 && rc!=2)
			{
				cout<<"\nInvalid entry. Enter: \n1. For Houses\n2. For Flats: ";
				cin>>rc;
			}
			if(rc==1)
			{
				house cm1,cm2;
			f1ptr.clear();
			f1ptr.read((char*)&cm1,sizeof(house));
			while(!f1ptr.eof())
			{
				if(tolower(cm1.purchasetype)=='r' && this->custid==cm1.ownerid)
				count++;
				f1ptr.read((char*)&cm1,sizeof(house));
			}
			if(count==0)
			{
				cout<<"\nNo available residential properties to display.\nPress any key to continue...";
				f3ptr.close();
				f2ptr.close();
				f1ptr.close();
				getchar();
				return 0;
			}
			else
			{
				int index=0;
				f1ptr.clear();
				f1ptr.seekg(0,ios::beg);
				house comarr[count];
				cout<<"\nSerial No. | Name | Size (Sq. Guz) | Available | Rooms | House Type | Purchase Type |  Floors | Furnished | Buy Price (Rs.)\n";
				f1ptr.read((char*)&cm1,sizeof(house));
				while(!f1ptr.eof())
				{
					if(tolower(cm1.purchasetype)=='r' && this->custid==cm1.ownerid)
					{
						comarr[index]=cm1;
						index+=1;
						if(cm1.available==1)
						strcpy(sr1,"YES");
						else
						strcpy(sr1,"NO");
						if(cm1.furnished==1)
						strcpy(sr2,"YES");
						else
						strcpy(sr2,"NO");
						
						printf("\n%-10d %-10s %.2f %-10s %10d %-10s %10c %10d %-10s %.2f",index,cm1.pname,cm1.psize,sr1,cm1.rooms,cm1.get_housetype(),toupper(cm1.purchasetype),cm1.floors,sr2,cm1.baserate);//co1.pname<<co1.psize<<sr1<<co1.get_shops()<<toupper(co1.purchasetype)<<co1.get_zonename()<<co1.baserate;
					}
					f1ptr.read((char*)&cm1,sizeof(house));
				}
				f1ptr.clear();
				cout<<"\nEnter desired property number: ";
				cin>>cho1;
				while(!(cho1>=1 && cho1<=count))
				{
					cout<<"\nInvalid entry. Enter valid property number: ";
					cin>>cho1;
				}
				cho1-=1;
				
				cout<<"\nProperty details: \n";
				comarr[cho1].displaydetails();
					cout<<"\n\nNow updating purchase type: \n";
				cout<<"\n*Existing rent history will be removed\n*The amount remaining from contract will be now charged from your account\n\n";
				if(comarr[cho1].propertyrent<comarr[cho1].baserate)
				{
					//updating customer
					customer testc;
					fstream testptr;
					string tname="CustomerInfo.dat";
					testptr.open(tname.c_str(),ios::in|ios::out|ios::binary);
					testptr.read((char*)&testc,sizeof(customer));
					while(!testptr.eof())
					{
						if(testc.custid==this->custid)
						{
							break;
						}
						testptr.read((char*)&testc,sizeof(customer));
					}
					cout<<"\nRemaining dues to be paid: "<<comarr[cho1].baserate-comarr[cho1].propertyrent<<endl<<endl;
					testc.acctotal+=comarr[cho1].baserate-comarr[cho1].propertyrent;
					testc.buytotal+=comarr[cho1].baserate-comarr[cho1].propertyrent;
					testc.renttotal-=comarr[cho1].propertyrent;
					copyobj(testc);
					testptr.seekp(-sizeof(customer),ios::cur);
					testptr.write((char*)&testc,sizeof(customer));
					testptr.close();
					//updating property
					comarr[cho1].propertyrent=0;
					comarr[cho1].purchasetype='b';
					f1ptr.clear();	
					f1ptr.seekg(0,ios::beg);
					f1ptr.read((char*)&cm1,sizeof(house));
					while(!f1ptr.eof())
					{
						if(cm1.ownerid==this->custid && cm1.propertyid==comarr[cho1].propertyid)
						break;
						f1ptr.read((char*)&cm1,sizeof(house));
					}
					f1ptr.seekp(-sizeof(house),ios::cur);
					f1ptr.write((char*)&comarr[cho1],sizeof(house));
					//updating agent
					agent agt;
					fstream agtptr;
					string fn="AgentInfo.dat";
					agtptr.open(fn.c_str(),ios::binary|ios::in|ios::out);
					agtptr.read((char*)&agt,sizeof(agent));
					while(!agtptr.eof())
					{
						if(comarr[cho1].get_sellerid()==agt.get_agentid())
						{
							break;
						}
						agtptr.read((char*)&agt,sizeof(agent));
					}
			
					agt.income=agt.income+((comarr[cho1].baserate-comarr[cho1].propertyrent)*(agt.crate/100));	
					agtptr.seekp(-sizeof(agent),ios::cur);
					agtptr.write((char*)&agt,sizeof(agent));
					agtptr.close();
				}
				else
				{
					//updating property
					comarr[cho1].propertyrent=0;
					comarr[cho1].purchasetype='b';
					f1ptr.clear();	
					f1ptr.seekg(0,ios::beg);
					f1ptr.read((char*)&cm1,sizeof(house));
					while(!f1ptr.eof())
					{
						if(cm1.ownerid==this->custid && cm1.propertyid==comarr[cho1].propertyid)
						break;
						f1ptr.read((char*)&cm1,sizeof(house));
					}
					f1ptr.seekp(-sizeof(house),ios::cur);
					f1ptr.write((char*)&comarr[cho1],sizeof(house));
					cout<<"\nRent has already been collected in full.\n";	
				}
				cout<<"\nProperty status successfully updated from rent to buy. Press any key to continue...";
				getchar();
			}
			}
			else
			{
				flat cm1,cm2;
				f2ptr.clear();
				f2ptr.read((char*)&cm1,sizeof(flat));
			while(!f2ptr.eof())
			{
				if(tolower(cm1.purchasetype)=='r' && this->custid==cm1.ownerid)
				count++;
				f2ptr.read((char*)&cm1,sizeof(flat));
			}
			if(count==0)
			{
				cout<<"\nNo available residential properties to display.\nPress any key to continue...";
				f3ptr.close();
				f2ptr.close();
				f1ptr.close();
				getchar();
				return 0;
			}
			else
			{
				int index=0;
				char sr3[50],sr4[50];
				f2ptr.clear();
				f2ptr.seekg(0,ios::beg);
				flat comarr[count];
				f2ptr.read((char*)&cm1,sizeof(flat));
				cout<<"\nSerial No. | Name | Size (Sq. Guz) | Available | Rooms | Parking | Purchase Type |  Elevator | Furnished | Buy Price (Rs.)\n";
				while(!f2ptr.eof())
				{
					if(tolower(cm1.purchasetype)=='r' && this->custid==cm1.ownerid)
					{
						comarr[index]=cm1;
						index+=1;
						if(cm1.available==1)
						strcpy(sr1,"YES");
						else
						strcpy(sr1,"NO");
						if(cm1.furnished==1)
						strcpy(sr2,"YES");
						else
						strcpy(sr2,"NO");
						if(cm1.get_parking()==1)
						strcpy(sr3,"YES");
						else
						strcpy(sr3,"NO");
						if(cm1.get_elevator()==1)
						strcpy(sr4,"YES");
						else
						strcpy(sr4,"NO");
						
						printf("\n%-10d %-10s %.2f %-10s %10d %-10s %10c %-10s %-10s %.2f",index,cm1.pname,cm1.psize,sr1,cm1.rooms,sr3,toupper(cm1.purchasetype),sr4,sr2,cm1.baserate);
					}
					f2ptr.read((char*)&cm1,sizeof(flat));
				}
				f2ptr.clear();
				cout<<"\nEnter desired property number: ";
				cin>>cho1;
				while(!(cho1>=1 && cho1<=count))
				{
					cout<<"\nInvalid entry. Enter valid property number: ";
					cin>>cho1;
				}
				cho1-=1;
				
				cout<<"\nProperty details: \n";
				comarr[cho1].displaydetails();
					cout<<"\n\nNow updating purchase type: \n";
				cout<<"\n*Existing rent history will be removed\n*The amount remaining from contract will be now charged from your account\n\n";
				if(comarr[cho1].propertyrent<comarr[cho1].baserate)
				{
					//updating customer
					customer testc;
					fstream testptr;
					string tname="CustomerInfo.dat";
					testptr.open(tname.c_str(),ios::in|ios::out|ios::binary);
					testptr.read((char*)&testc,sizeof(customer));
					while(!testptr.eof())
					{
						if(testc.custid==this->custid)
						{
							break;
						}
						testptr.read((char*)&testc,sizeof(customer));
					}
					cout<<"\n\nRemaining dues to be paid: "<<comarr[cho1].baserate-comarr[cho1].propertyrent<<endl<<endl;
					testc.acctotal+=comarr[cho1].baserate-comarr[cho1].propertyrent;
					testc.buytotal+=comarr[cho1].baserate-comarr[cho1].propertyrent;
					testc.renttotal-=comarr[cho1].propertyrent;
					copyobj(testc);
					testptr.seekp(-sizeof(customer),ios::cur);
					testptr.write((char*)&testc,sizeof(customer));
					testptr.close();
					//updating property
					comarr[cho1].propertyrent=0;
					comarr[cho1].purchasetype='b';
					f2ptr.clear();	
					f2ptr.seekg(0,ios::beg);
					f2ptr.read((char*)&cm1,sizeof(flat));
					while(!f2ptr.eof())
					{
						if(cm1.ownerid==this->custid && cm1.propertyid==comarr[cho1].propertyid)
						break;
						f2ptr.read((char*)&cm1,sizeof(flat));
					}
					f2ptr.seekp(-sizeof(flat),ios::cur);
					f2ptr.write((char*)&comarr[cho1],sizeof(flat));
					//updating agent
					agent agt;
					fstream agtptr;
					string fn="AgentInfo.dat";
					agtptr.open(fn.c_str(),ios::binary|ios::in|ios::out);
					agtptr.read((char*)&agt,sizeof(agent));
					while(!agtptr.eof())
					{
						if(comarr[cho1].get_sellerid()==agt.get_agentid())
						{
							break;
						}
						agtptr.read((char*)&agt,sizeof(agent));
					}
			
					agt.income=agt.income+((comarr[cho1].baserate-comarr[cho1].propertyrent)*(agt.crate/100));	
					agtptr.seekp(-sizeof(agent),ios::cur);
					agtptr.write((char*)&agt,sizeof(agent));
					agtptr.close();
				}
				else
				{
					//updating property
					comarr[cho1].propertyrent=0;
					comarr[cho1].purchasetype='b';
					f2ptr.clear();	
					f2ptr.seekg(0,ios::beg);
					f2ptr.read((char*)&cm1,sizeof(flat));
					while(!f2ptr.eof())
					{
						if(cm1.ownerid==this->custid && cm1.propertyid==comarr[cho1].propertyid)
						break;
						f2ptr.read((char*)&cm1,sizeof(flat));
					}
					f2ptr.seekp(-sizeof(flat),ios::cur);
					f2ptr.write((char*)&comarr[cho1],sizeof(flat));
					cout<<"\nRent has already been collected in full.\n";	
				}
				cout<<"\nProperty status successfully updated from rent to buy. Press any key to continue...";
				getchar();
			
			}	
			}//
		}
	f3ptr.close();
	f2ptr.close();
	f1ptr.close();	
	cout<<"\n\nPress any key to continue...";
	getchar();
	getchar();
	
	}

};

//member function to view both sold and unsold properties*
int agent::view_sold_properties()
	{
		int choice1;
		int pchoice,cho1;
		fstream f1ptr,f2ptr,f3ptr;
		string str1="House.dat";
		string str2="Flats.dat";
		string str3="Commercial.dat";
		
		f1ptr.open(str1.c_str(),ios::binary|ios::in|ios::out);
		f2ptr.open(str2.c_str(),ios::binary|ios::in|ios::out);
		f3ptr.open(str3.c_str(),ios::binary|ios::in|ios::out);
		f1ptr.seekg(0,ios::end);
		f2ptr.seekg(0,ios::end);
		f3ptr.seekg(0,ios::end);
		
		if(f1ptr.tellg()==0 && f2ptr.tellg()==0 && f3ptr.tellg()==0)
		{
			cout<<"\nError. No records to display.\n\n";
		}
		
		f1ptr.seekg(0,ios::beg);
		f2ptr.seekg(0,ios::beg);
		f3ptr.seekg(0,ios::beg);
		int count=0;
		int p1;
		char sr1[20],sr2[20];
		cout<<"\n*************YOUR PROPERTIES*************\n\n";
		cout<<"Which properties would you like to view?\n1. Sold Properties(Unavailable)\n2. Unsold Available Properties\n\nEnter your choice: ";
		cin>>choice1;
		while(choice1<1 || choice1>2)
		{
			cout<<"\nInvalid choice entered. Please enter a valid choice: ";
			cin>>choice1;
		}
		cout<<"\n**********PROPERTIES**********\n\n\n";
		cout<<"******PROPERTY TYPE******\n\n1. RESIDENTIAL\n2. COMMERCIAL\nEnter your choice: ";
		cin>>pchoice;
		while(pchoice<1 || pchoice>2)
		{
				cout<<"\nInvalid entry! Enter valid choice: ";
				cin>>pchoice;
		}
		
		if(choice1==1)
		{
			cout<<"\nSold properties...\n\n";
			if(pchoice==2)
			{
				commercial cm1,cm2;
			f3ptr.clear();
			f3ptr.seekg(0,ios::beg);
			f3ptr.read((char*)&cm1,sizeof(commercial));
			while(!f3ptr.eof())
			{
				if((this->agentid)==cm1.sellerid && cm1.ownerid!=cm1.sellerid)
				count++;
				f3ptr.read((char*)&cm1,sizeof(commercial));
			}
			if(count==0)
			{
				cout<<"\nNo available commercial properties to display.\nPress any key to continue...";
				f3ptr.close();
				f2ptr.close();
				f1ptr.close();
				getchar();
				return 1;
				
			}
			else
			{
				int index=0;
				f3ptr.clear();
				f3ptr.seekg(0,ios::beg);
				commercial comarr[count];
				f3ptr.read((char*)&cm1,sizeof(commercial));
				
				cout<<"\nSerial No. | Name | Size | Available | Shops | Facing Type | Purchase Type | Commercial Zone | Buy Price (Rs.)\n";
				while(!f3ptr.eof())
				{
					if((this->agentid)==cm1.sellerid && cm1.ownerid!=cm1.sellerid)
					{
					comarr[index]=cm1;
					index+=1;
					strcpy(sr1,"YES");
					
					if(cm1.get_shoplocation()=='i')
					strcpy(sr2,"Internal");
					else
					strcpy(sr2,"Front Facing");

					printf("\n%-10d %-10s %.2f %-10s %10d %-10s %10c %10s %.2f",index,cm1.pname,cm1.psize,sr1,cm1.get_shops(),sr2,toupper(cm1.purchasetype),cm1.get_zonename(),cm1.baserate);
					}//print statement
					f3ptr.read((char*)&cm1,sizeof(commercial));
				}
				f3ptr.clear();
				cout<<"\nEnter desired property number: ";
				cin>>cho1;
				while(!(cho1>=1 && cho1<=count))
				{
					cout<<"\nInvalid entry. Enter valid property number: ";
					cin>>cho1;
				}
				cho1-=1;
				
				cout<<"\nProperty details: \n";
				comarr[cho1].displaydetails();
				comarr[cho1].viewcontract(tolower(comarr[cho1].purchasetype));
				
				int rentch;
				if(tolower(comarr[cho1].purchasetype)=='r')
				{
					cout<<"\nDo you wish to access rent details for this property? Enter 1 for yes, 2 for no: ";
					cin>>rentch;
					if(rentch==1)
					{
						collect_rent(comarr[cho1]);
					}
				}
				cout<<"\nPress any key to continue...";
				getchar();
			}
			}
			else if(pchoice==1)
			{
				int rc;//hosues and flats
			cout<<"\nEnter: \n1. For Houses\n2. For Flats: ";
			cin>>rc;
			while(rc!=1 && rc!=2)
			{
				cout<<"\nInvalid entry. Enter: \n1. For Houses\n2. For Flats: ";
				cin>>rc;
			}
			if(rc==1)
			{
				house cm1,cm2;
			f1ptr.clear();
			f1ptr.read((char*)&cm1,sizeof(house));
			while(!f1ptr.eof())
			{
				if((this->agentid)==cm1.sellerid && cm1.ownerid!=cm1.sellerid)
				count++;
				f1ptr.read((char*)&cm1,sizeof(house));
			}
			if(count==0)
			{
				cout<<"\nNo available residential properties to display.\nPress any key to continue...";
				f3ptr.close();
				f2ptr.close();
				f1ptr.close();
				getchar();
				return 0;
			}
			else
			{
				int index=0;
				f1ptr.clear();
				f1ptr.seekg(0,ios::beg);
				house comarr[count];
				cout<<"\nSerial No. | Name | Size (Sq. Guz) | Available | Rooms | House Type | Purchase Type |  Floors | Furnished | Buy Price (Rs.)\n";
				f1ptr.read((char*)&cm1,sizeof(house));
				while(!f1ptr.eof())
				{
					if((this->agentid)==cm1.sellerid && cm1.ownerid!=cm1.sellerid)
					{
						comarr[index]=cm1;
						index+=1;
						if(cm1.available==1)
						strcpy(sr1,"YES");
						else
						strcpy(sr1,"NO");
						if(cm1.furnished==1)
						strcpy(sr2,"YES");
						else
						strcpy(sr2,"NO");
						
						printf("\n%-10d %-10s %.2f %-10s %10d %-10s %10c %10d %-10s %.2f",index,cm1.pname,cm1.psize,sr1,cm1.rooms,cm1.get_housetype(),toupper(cm1.purchasetype),cm1.floors,sr2,cm1.baserate);//co1.pname<<co1.psize<<sr1<<co1.get_shops()<<toupper(co1.purchasetype)<<co1.get_zonename()<<co1.baserate;
					}
					f1ptr.read((char*)&cm1,sizeof(house));
				}
				f1ptr.clear();
				cout<<"\nEnter desired property number: ";
				cin>>cho1;
				while(!(cho1>=1 && cho1<=count))
				{
					cout<<"\nInvalid entry. Enter valid property number: ";
					cin>>cho1;
				}
				cho1-=1;
				
				cout<<"\nProperty details: \n";
				comarr[cho1].displaydetails();
				comarr[cho1].viewcontract(tolower(comarr[cho1].purchasetype));
				
				int rentch;
				if(tolower(comarr[cho1].purchasetype)=='r')
				{
					cout<<"\nDo you wish to access rent details for this property? Enter 1 for yes, 2 for no: ";
					cin>>rentch;
					if(rentch==1)
					{
						collect_rent(comarr[cho1]);
					}
				}
				cout<<"\nPress any key to continue...";
				getchar();
			}
			}
			else
			{
				flat cm1,cm2;
				f2ptr.clear();
				f2ptr.read((char*)&cm1,sizeof(flat));
			while(!f2ptr.eof())
			{
				if((this->agentid)==cm1.sellerid && cm1.ownerid!=cm1.sellerid)
				count++;
				f2ptr.read((char*)&cm1,sizeof(flat));
			}
			if(count==0)
			{
				cout<<"\nNo available residential properties to display.\nPress any key to continue...";
				f3ptr.close();
				f2ptr.close();
				f1ptr.close();
				getchar();
				return 0;
			}
			else
			{
				int index=0;
				char sr3[50],sr4[50];
				f2ptr.clear();
				f2ptr.seekg(0,ios::beg);
				flat comarr[count];
				f2ptr.read((char*)&cm1,sizeof(flat));
				cout<<"\nSerial No. | Name | Size (Sq. Guz) | Available | Rooms | Parking | Purchase Type |  Elevator | Furnished | Buy Price (Rs.)\n";
				while(!f2ptr.eof())
				{
					if((this->agentid)==cm1.sellerid && cm1.ownerid!=cm1.sellerid)
					{
						comarr[index]=cm1;
						index+=1;
						if(cm1.available==1)
						strcpy(sr1,"YES");
						else
						strcpy(sr1,"NO");
						if(cm1.furnished==1)
						strcpy(sr2,"YES");
						else
						strcpy(sr2,"NO");
						if(cm1.get_parking()==1)
						strcpy(sr3,"YES");
						else
						strcpy(sr3,"NO");
						if(cm1.get_elevator()==1)
						strcpy(sr4,"YES");
						else
						strcpy(sr4,"NO");
						
						printf("\n%-10d %-10s %.2f %-10s %10d %-10s %10c %-10s %-10s %.2f",index,cm1.pname,cm1.psize,sr1,cm1.rooms,sr3,toupper(cm1.purchasetype),sr4,sr2,cm1.baserate);
					}
					f2ptr.read((char*)&cm1,sizeof(flat));
				}
				f2ptr.clear();
				cout<<"\nEnter desired property number: ";
				cin>>cho1;
				while(!(cho1>=1 && cho1<=count))
				{
					cout<<"\nInvalid entry. Enter valid property number: ";
					cin>>cho1;
				}
				cho1-=1;
				
				cout<<"\nProperty details: \n";
				comarr[cho1].displaydetails();
				comarr[cho1].viewcontract(tolower(comarr[cho1].purchasetype));
				
				int rentch;
				if(tolower(comarr[cho1].purchasetype)=='r')
				{
					cout<<"\nDo you wish to access rent details for this property? Enter 1 for yes, 2 for no: ";
					cin>>rentch;
					if(rentch==1)
					{
						collect_rent(comarr[cho1]);
					}
				}
				cout<<"\nPress any key to continue...";
				getchar();
			
			}	
			}//
			}
			
			
		}
		else if(choice1==2)
		{
				cout<<"\nUnsold properties...\n\n";
			if(pchoice==2)
			{
				commercial cm1,cm2;
			f3ptr.clear();
			f3ptr.seekg(0,ios::beg);
			f3ptr.read((char*)&cm1,sizeof(commercial));
			while(!f3ptr.eof())
			{
				if((this->agentid)==cm1.sellerid && cm1.ownerid==cm1.sellerid)
				count++;
				f3ptr.read((char*)&cm1,sizeof(commercial));
			}
			if(count==0)
			{
				cout<<"\nNo available commercial properties to display.\nPress any key to continue...";
				f3ptr.close();
				f2ptr.close();
				f1ptr.close();
				getchar();
				getchar();
				return 1;
				
			}
			else
			{
				int index=0;
				f3ptr.clear();
				f3ptr.seekg(0,ios::beg);
				commercial comarr[count];
				f3ptr.read((char*)&cm1,sizeof(commercial));
				
				cout<<"\nSerial No. | Name | Size | Available | Shops | Facing Type | Purchase Type | Commercial Zone | Buy Price (Rs.)\n";
				while(!f3ptr.eof())
				{
					if((this->agentid)==cm1.sellerid && cm1.ownerid==cm1.sellerid)
					{
					comarr[index]=cm1;
					index+=1;
					strcpy(sr1,"YES");
					
					if(cm1.get_shoplocation()=='i')
					strcpy(sr2,"Internal");
					else
					strcpy(sr2,"Front Facing");

					printf("\n%-10d %-10s %.2f %-10s %10d %-10s %10c %10s %.2f",index,cm1.pname,cm1.psize,sr1,cm1.get_shops(),sr2,toupper(cm1.purchasetype),cm1.get_zonename(),cm1.baserate);
					}//print statement
					f3ptr.read((char*)&cm1,sizeof(commercial));
				}
				f3ptr.clear();
				cout<<"\nEnter desired property number: ";
				cin>>cho1;
				while(!(cho1>=1 && cho1<=count))
				{
					cout<<"\nInvalid entry. Enter valid property number: ";
					cin>>cho1;
				}
				cho1-=1;
				
				cout<<"\nProperty details: \n";
				comarr[cho1].displaydetails();
				//comarr[cho1].viewcontract(tolower(comarr[cho1].purchasetype));
				cout<<"\nPress any key to continue...";
				getchar();
				getchar();
			}
			}
			else if(pchoice==1)
			{
				int rc;//hosues and flats
			cout<<"\nEnter: \n1. For Houses\n2. For Flats: ";
			cin>>rc;
			while(rc!=1 && rc!=2)
			{
				cout<<"\nInvalid entry. Enter: \n1. For Houses\n2. For Flats: ";
				cin>>rc;
			}
			if(rc==1)
			{
				house cm1,cm2;
			f1ptr.clear();
			f1ptr.read((char*)&cm1,sizeof(house));
			while(!f1ptr.eof())
			{
				if((this->agentid)==cm1.sellerid && cm1.ownerid==cm1.sellerid)
				count++;
				f1ptr.read((char*)&cm1,sizeof(house));
			}
			if(count==0)
			{
				cout<<"\nNo available residential properties to display.\nPress any key to continue...";
				f3ptr.close();
				f2ptr.close();
				f1ptr.close();
				getchar();
				getchar();
				return 0;
			}
			else
			{
				int index=0;
				f1ptr.clear();
				f1ptr.seekg(0,ios::beg);
				house comarr[count];
				cout<<"\nSerial No. | Name | Size (Sq. Guz) | Available | Rooms | House Type | Purchase Type |  Floors | Furnished | Buy Price (Rs.)\n";
				f1ptr.read((char*)&cm1,sizeof(house));
				while(!f1ptr.eof())
				{
					if((this->agentid)==cm1.sellerid && cm1.ownerid==cm1.sellerid)
					{
						comarr[index]=cm1;
						index+=1;
						if(cm1.available==1)
						strcpy(sr1,"YES");
						else
						strcpy(sr1,"NO");
						if(cm1.furnished==1)
						strcpy(sr2,"YES");
						else
						strcpy(sr2,"NO");
						
						printf("\n%-10d %-10s %.2f %-10s %10d %-10s %10c %10d %-10s %.2f",index,cm1.pname,cm1.psize,sr1,cm1.rooms,cm1.get_housetype(),toupper(cm1.purchasetype),cm1.floors,sr2,cm1.baserate);//co1.pname<<co1.psize<<sr1<<co1.get_shops()<<toupper(co1.purchasetype)<<co1.get_zonename()<<co1.baserate;
					}
					f1ptr.read((char*)&cm1,sizeof(house));
				}
				f1ptr.clear();
				cout<<"\nEnter desired property number: ";
				cin>>cho1;
				while(!(cho1>=1 && cho1<=count))
				{
					cout<<"\nInvalid entry. Enter valid property number: ";
					cin>>cho1;
				}
				cho1-=1;
				
				cout<<"\nProperty details: \n";
				comarr[cho1].displaydetails();
				//comarr[cho1].viewcontract(tolower(comarr[cho1].purchasetype));
				cout<<"\nPress any key to continue...";
				getchar();
				getchar();
			}
			}
			else
			{
				flat cm1,cm2;
				f2ptr.clear();
				f2ptr.read((char*)&cm1,sizeof(flat));
			while(!f2ptr.eof())
			{
				if((this->agentid)==cm1.sellerid && cm1.ownerid==cm1.sellerid)
				count++;
				f2ptr.read((char*)&cm1,sizeof(flat));
			}
			if(count==0)
			{
				cout<<"\nNo available residential properties to display.\nPress any key to continue...";
				f3ptr.close();
				f2ptr.close();
				f1ptr.close();
				getchar();
				return 0;
			}
			else
			{
				int index=0;
				char sr3[50],sr4[50];
				f2ptr.clear();
				f2ptr.seekg(0,ios::beg);
				flat comarr[count];
				f2ptr.read((char*)&cm1,sizeof(flat));
				cout<<"\nSerial No. | Name | Size (Sq. Guz) | Available | Rooms | Parking | Purchase Type |  Elevator | Furnished | Buy Price (Rs.)\n";
				while(!f2ptr.eof())
				{
					if((this->agentid)==cm1.sellerid && cm1.ownerid==cm1.sellerid)
					{
						comarr[index]=cm1;
						index+=1;
						if(cm1.available==1)
						strcpy(sr1,"YES");
						else
						strcpy(sr1,"NO");
						if(cm1.furnished==1)
						strcpy(sr2,"YES");
						else
						strcpy(sr2,"NO");
						if(cm1.get_parking()==1)
						strcpy(sr3,"YES");
						else
						strcpy(sr3,"NO");
						if(cm1.get_elevator()==1)
						strcpy(sr4,"YES");
						else
						strcpy(sr4,"NO");
						
						printf("\n%-10d %-10s %.2f %-10s %10d %-10s %10c %-10s %-10s %.2f",index,cm1.pname,cm1.psize,sr1,cm1.rooms,sr3,toupper(cm1.purchasetype),sr4,sr2,cm1.baserate);
					}
					f2ptr.read((char*)&cm1,sizeof(flat));
				}
				f2ptr.clear();
				cout<<"\nEnter desired property number: ";
				cin>>cho1;
				while(!(cho1>=1 && cho1<=count))
				{
					cout<<"\nInvalid entry. Enter valid property number: ";
					cin>>cho1;
				}
				cho1-=1;
				
				cout<<"\nProperty details: \n";
				comarr[cho1].displaydetails();
				//comarr[cho1].viewcontract(tolower(comarr[cho1].purchasetype));
				cout<<"\nPress any key to continue...";
				getchar();
				getchar();
			
			}	
			}//
			}
			
			
		}
		f1ptr.close();
		f2ptr.close();
		f3ptr.close();
	}
//overloaded rent collection member function for commercial objects
	int agent::collect_rent(commercial rcom)
	{
		int con;
		cout<<"\nRent history already displayed. Collect rent for next month?\n1. Yes\n2. No\n\nEnter your choice: ";
		cin>>con;
		while(con!=1 && con!=2)
		{
			cout<<"\nInvalid entry. Please enter valid choice: ";
			cin>>con;
		}
		if(con==1)
		{
			//updating customer
			fstream custptr;
			customer cr1;
			string cname="CustomerInfo.dat";
			custptr.open(cname.c_str(),ios::binary|ios::in|ios::out);
			if(!custptr)
			{
				cout<<"\nError opening file.\n";
				exit(1);
			}
			custptr.read((char*)&cr1,sizeof(customer));
			while(!custptr.eof())
			{
				if(cr1.get_custid()==rcom.ownerid)
				{
					break;				
				}
				custptr.read((char*)&cr1,sizeof(customer));
			}
			
			custptr.clear();
			cr1.renttotal+=rcom.monthrent;
			cr1.acctotal+=rcom.monthrent;
			if(cr1.budget!=-1)
			{
			cr1.budget-=rcom.monthrent;		
			}
			custptr.seekp(-sizeof(customer),ios::cur);
			custptr.write((char*)&cr1,sizeof(customer));
			custptr.close();
			
			//updating property
			fstream comptr;
			commercial com1;
			string cn="Commercial.dat";
			comptr.open(cn.c_str(),ios::binary|ios::in|ios::out);
			if(!comptr)
			{
				cout<<"\nError opening file.\n";
				exit(1);
			}
			comptr.read((char*)&com1,sizeof(commercial));
			while(!comptr.eof())
			{
				if(com1.propertyid==rcom.propertyid)
				{
					break;				
				}
				comptr.read((char*)&com1,sizeof(commercial));
			}
			
			comptr.clear();
			com1.propertyrent+=com1.monthrent;
			comptr.seekp(-sizeof(commercial),ios::cur);
			comptr.write((char*)&com1,sizeof(commercial));
			comptr.close();
			cout<<"\nUpdated Rent History: \n\n";
			com1.displayRentHistory();
			
			//updating agent
			agent agt;
					fstream agtptr;
					string fn="AgentInfo.dat";
					agtptr.open(fn.c_str(),ios::binary|ios::in|ios::out);
					agtptr.read((char*)&agt,sizeof(agent));
					while(!agtptr.eof())
					{
						if(rcom.get_sellerid()==agt.get_agentid())
						{
							break;
						}
						agtptr.read((char*)&agt,sizeof(agent));
					}
			
			agt.income=agt.income+((rcom.monthrent)*(agt.crate/100));
			agt.rentcollected+=rcom.monthrent;	
			this->copyobj(agt);
			agtptr.seekp(-sizeof(agent),ios::cur);
			agtptr.write((char*)&agt,sizeof(agent));
			agtptr.close();
			
			
			
		}
		cout<<"\nProperty, Customer, Agent information now updated. Press any key to continue\n";
		getchar();
	
	}
	//overloaded rent collection member function for house objects
	int agent::collect_rent(house rcom)
	{
			int con;
		cout<<"\nRent history already displayed. Collect rent for next month?\n1. Yes\n2. No\n\nEnter your choice: ";
		cin>>con;
		while(con!=1 && con!=2)
		{
			cout<<"\nInvalid entry. Please enter valid choice: ";
			cin>>con;
		}
		if(con==1)
		{
			//updating customer
			fstream custptr;
			customer cr1;
			string cname="CustomerInfo.dat";
			custptr.open(cname.c_str(),ios::binary|ios::in|ios::out);
			if(!custptr)
			{
				cout<<"\nError opening file.\n";
				exit(1);
			}
			custptr.read((char*)&cr1,sizeof(customer));
			while(!custptr.eof())
			{
				if(cr1.get_custid()==rcom.ownerid)
				{
					break;				
				}
				custptr.read((char*)&cr1,sizeof(customer));
			}
			
			custptr.clear();
			cr1.renttotal+=rcom.monthrent;
			cr1.acctotal+=rcom.monthrent;
			if(cr1.budget!=-1)
			{
			cr1.budget-=rcom.monthrent;		
			}
			custptr.seekp(-sizeof(customer),ios::cur);
			custptr.write((char*)&cr1,sizeof(customer));
			custptr.close();
			
			//updating property
			fstream comptr;
			house com1;
			string cn="House.dat";
			comptr.open(cn.c_str(),ios::binary|ios::in|ios::out);
			if(!comptr)
			{
				cout<<"\nError opening file.\n";
				exit(1);
			}
			comptr.read((char*)&com1,sizeof(house));
			while(!comptr.eof())
			{
				if(com1.propertyid==rcom.propertyid)
				{
					break;				
				}
				comptr.read((char*)&com1,sizeof(house));
			}
			
			comptr.clear();
			com1.propertyrent+=com1.monthrent;
			comptr.seekp(-sizeof(house),ios::cur);
			comptr.write((char*)&com1,sizeof(house));
			comptr.close();
			cout<<"\nUpdated Rent History: \n\n";
			com1.displayRentHistory();
			
			//updating agent
			agent agt;
					fstream agtptr;
					string fn="AgentInfo.dat";
					agtptr.open(fn.c_str(),ios::binary|ios::in|ios::out);
					agtptr.read((char*)&agt,sizeof(agent));
					while(!agtptr.eof())
					{
						if(rcom.get_sellerid()==agt.get_agentid())
						{
							break;
						}
						agtptr.read((char*)&agt,sizeof(agent));
					}
			
			agt.income=agt.income+((rcom.monthrent)*(agt.crate/100));
			agt.rentcollected+=rcom.monthrent;	
			this->copyobj(agt);
			agtptr.seekp(-sizeof(agent),ios::cur);
			agtptr.write((char*)&agt,sizeof(agent));
			agtptr.close();
			
			
			
		}
		cout<<"\nProperty, Customer, Agent information now updated. Press any key to continue\n";
		getchar();
	
	}
	//overloaded rent collection member function for flat objects
	int agent::collect_rent(flat rcom)
	{
			int con;
		cout<<"\nRent history already displayed. Collect rent for next month?\n1. Yes\n2. No\n\nEnter your choice: ";
		cin>>con;
		while(con!=1 && con!=2)
		{
			cout<<"\nInvalid entry. Please enter valid choice: ";
			cin>>con;
		}
		if(con==1)
		{
			//updating customer
			fstream custptr;
			customer cr1;
			string cname="CustomerInfo.dat";
			custptr.open(cname.c_str(),ios::binary|ios::in|ios::out);
			if(!custptr)
			{
				cout<<"\nError opening file.\n";
				exit(1);
			}
			custptr.read((char*)&cr1,sizeof(customer));
			while(!custptr.eof())
			{
				if(cr1.get_custid()==rcom.ownerid)
				{
					break;				
				}
				custptr.read((char*)&cr1,sizeof(customer));
			}
			
			custptr.clear();
			cr1.renttotal+=rcom.monthrent;
			cr1.acctotal+=rcom.monthrent;
			if(cr1.budget!=-1)
			{
				cr1.budget-=rcom.monthrent;
			}
			custptr.seekp(-sizeof(customer),ios::cur);
			custptr.write((char*)&cr1,sizeof(customer));
			custptr.close();
			
			//updating property
			fstream comptr;
			flat com1;
			string cn="Flats.dat";
			comptr.open(cn.c_str(),ios::binary|ios::in|ios::out);
			if(!comptr)
			{
				cout<<"\nError opening file.\n";
				exit(1);
			}
			comptr.read((char*)&com1,sizeof(flat));
			while(!comptr.eof())
			{
				if(com1.propertyid==rcom.propertyid)
				{
					break;				
				}
				comptr.read((char*)&com1,sizeof(flat));
			}
			
			comptr.clear();
			com1.propertyrent+=com1.monthrent;
			comptr.seekp(-sizeof(flat),ios::cur);
			comptr.write((char*)&com1,sizeof(flat));
			comptr.close();
			cout<<"\nUpdated Rent History: \n\n";
			com1.displayRentHistory();
			
			//updating agent
			agent agt;
					fstream agtptr;
					string fn="AgentInfo.dat";
					agtptr.open(fn.c_str(),ios::binary|ios::in|ios::out);
					agtptr.read((char*)&agt,sizeof(agent));
					while(!agtptr.eof())
					{
						if(rcom.get_sellerid()==agt.get_agentid())
						{
							break;
						}
						agtptr.read((char*)&agt,sizeof(agent));
					}
			
			agt.income=agt.income+((rcom.monthrent)*(agt.crate/100));
			agt.rentcollected+=rcom.monthrent;	
			this->copyobj(agt);
			agtptr.seekp(-sizeof(agent),ios::cur);
			agtptr.write((char*)&agt,sizeof(agent));
			agtptr.close();
			
			
			
		}
		cout<<"\nProperty, Customer, Agent information now updated. Press any key to continue\n";
		getchar();
	} 
	
//function for viewing properties with certain FILTERS
//includes sorting properties by location	
int ViewProperties()
{
		int pchoice;
		fstream f1ptr,f2ptr,f3ptr;
		string str1="House.dat";
		string str2="Flats.dat";
		string str3="Commercial.dat";
		
		f1ptr.open(str1.c_str(),ios::binary|ios::in|ios::out);
		f2ptr.open(str2.c_str(),ios::binary|ios::in|ios::out);
		f3ptr.open(str3.c_str(),ios::binary|ios::in|ios::out);
		f1ptr.seekg(0,ios::end);
		f2ptr.seekg(0,ios::end);
		f3ptr.seekg(0,ios::end);
		
		if(!f1ptr || !f2ptr || !f3ptr)
		{
			cout<<"\nCould not open files.\n";
			exit(1);
		}
		
		if(f1ptr.tellg()==0 && f2ptr.tellg()==0 && f3ptr.tellg()==0)
		{
			cout<<"\nError. No records to display.\n\n";
		}
		
		f1ptr.seekg(0,ios::beg);
		f2ptr.seekg(0,ios::beg);
		f3ptr.seekg(0,ios::beg);
		int count=0;
		int index=0;
		int p1,inchoice;
		char sr1[20],sr2[20];
		cout<<"\n**********PROPERTIES**********\n\n\n";
		cout<<"******PROPERTY TYPE******\n\n1. RESIDENTIAL\n2. COMMERCIAL\nEnter your choice: ";
		cin>>pchoice;
		while(pchoice<1 || pchoice>2)
		{
				cout<<"\nInvalid entry! Enter valid choice: ";
				cin>>pchoice;
		}
		//cout<<"Filter by:\n\n1. Property Type (Commercial, Residential)\n2. Buy Type (Buy, Rent)\n3. Filter by price\n4. By region\n\nEnter your choice: ";
		if(pchoice==2)
		{
			commercial co1;
			cout<<"\n\nVIEW MENU\n\nFilter by:\n1. Number of Shops\n2. Facing Type (Front or Internal)\n3. Location\n4. Price\n\nEnter your choice: ";
			cin>>p1;
			while(p1<1 || p1>4)
			{
				cout<<"\nInvalid entry! Enter valid choice: ";
				cin>>p1;
			}
			
			if(p1==1)
			{
				int min,max;
			
				cout<<"\nEnter minimum and maximum number of desired shops (min max): ";
				cin>>min>>max;
				while((min>max) || (min<=0) || (max<=0))
				{
					cout<<"\nInvalid entry. Enter minimum and maximum number of desired shops (min max): ";
					cin>>min>>max;
				}
				
				f3ptr.read((char*)&co1,sizeof(commercial));
				while(!f3ptr.eof())
				{
					if((co1.get_shops()>=min && co1.get_shops()<=max) && co1.available==1)
					count++;
					f3ptr.read((char*)&co1,sizeof(commercial));
				}
				if(count==0)
				{
					cout<<"\n\nNo available properties that match your criteria. Press any key to continue.\n\n";
					f3ptr.close();
					f2ptr.close();
					f1ptr.close();
					getchar();
					return 1;
				}
				commercial comarr[count];
				cout<<"\n\nNow displaying properties:\n\nName |\t Size |\t Available |\t Shops |\t Facing Type |\t Purchase Type |\t Commercial Zone |\t Buy Price (Rs.) |\n";
				f3ptr.clear();
				f3ptr.seekg(0,ios::beg);
				f3ptr.read((char*)&co1,sizeof(commercial));
				while(!f3ptr.eof())
				{
					if((co1.get_shops()>=min && co1.get_shops()<=max) && co1.available==1)
					{
						Sleep(200);
						comarr[index]=co1;
						index++;
						if(co1.available==1)
						strcpy(sr1,"YES");
						else
						strcpy(sr1,"NO");
						if(co1.get_shoplocation()=='i')
						strcpy(sr2,"Internal");
						else
						strcpy(sr2,"Front Facing");
						
						printf("\n%10d %-10s %.2f %-10s %10d %-10s %10c %10s %.2f",index,co1.pname,co1.psize,sr1,co1.get_shops(),sr2,toupper(co1.purchasetype),co1.get_zonename(),co1.baserate);//co1.pname<<co1.psize<<sr1<<co1.get_shops()<<toupper(co1.purchasetype)<<co1.get_zonename()<<co1.baserate;
					}
					f3ptr.read((char*)&co1,sizeof(commercial));
				}
				
				while(1)
				{
				cout<<"\nEnter desired property number: ";
				cin>>inchoice;
				if(inchoice<1 || inchoice>count)
				{
					cout<<"\nInvalid entry. Enter valid choice: ";
				}
				else
				break;
				}
				inchoice-=1;
				comarr[inchoice].displaydetails();
				cout<<"\n\nAll details now displayed. Press any key to continue...";
				getchar();
				getchar();
			}
			else if(p1==2)
			{
				int ch2;
				cout<<"\nFACE TYPES:\n1. Internally located\n2. Front Facing\nEnter your choice: ";
				cin>>ch2;
				if(ch2==1)
				{
				f3ptr.read((char*)&co1,sizeof(commercial));
				while(!f3ptr.eof())
				{
					if((tolower(co1.get_shoplocation())=='i') && co1.available==1)
					count++;
					f3ptr.read((char*)&co1,sizeof(commercial));
				}
				if(count==0)
				{
					cout<<"\n\nNo available properties that match your criteria. Press any key to continue.\n\n";
					f3ptr.close();
					f2ptr.close();
					f1ptr.close();
					getchar();
					getchar();
					return 1;
				}
				commercial comarr[count];
				f3ptr.clear();
				f3ptr.seekg(0,ios::beg);
				//f3ptr.read((char*)&co1,sizeof(commercial));
				cout<<"\nName | Size | Available | Shops | Facing Type | Purchase Type | Commercial Zone | Buy Price (Rs.)\n";
				f3ptr.read((char*)&co1,sizeof(commercial));
				while(!f3ptr.eof())
				{
					if((tolower(co1.get_shoplocation())=='i') && co1.available==1)
					{
						Sleep(200);
						comarr[index]=co1;
						index++;
						if(co1.available==1)
						strcpy(sr1,"YES");
						else
						strcpy(sr1,"NO");
						if(co1.get_shoplocation()=='i')
						strcpy(sr2,"Internal");
						else
						strcpy(sr2,"Front Facing");
						
						printf("\n%10d %-10s %.2f %-10s %10d %-10s %10c %10s %.2f",index,co1.pname,co1.psize,sr1,co1.get_shops(),sr2,toupper(co1.purchasetype),co1.get_zonename(),co1.baserate);//co1.pname<<co1.psize<<sr1<<co1.get_shops()<<toupper(co1.purchasetype)<<co1.get_zonename()<<co1.baserate;
					}
					f3ptr.read((char*)&co1,sizeof(commercial));
				}
				
				while(1)
				{
					cout<<"\nEnter desired property number: ";
					cin>>inchoice;
					if(inchoice<1 || inchoice>count)
					{
						cout<<"\nInvalid entry. Enter valid choice: ";
					}
					else
					break;
				}
				inchoice-=1;
				comarr[inchoice].displaydetails();
				cout<<"\n\nAll details now displayed. Press any key to continue...";
				getchar();
				getchar();
				}
				else
				{
					f3ptr.read((char*)&co1,sizeof(commercial));
				while(!f3ptr.eof())
				{
					if((tolower(co1.get_shoplocation())=='e') && co1.available==1)
					count++;
					f3ptr.read((char*)&co1,sizeof(commercial));
				}
				if(count==0)
				{
					cout<<"\n\nNo available properties that match your criteria. Press any key to continue.\n\n";
					f3ptr.close();
					f2ptr.close();
					f1ptr.close();
					getchar();
					getchar();
					return 1;
				}
				commercial comarr[count];
				f3ptr.clear();
				f3ptr.seekg(0,ios::beg);
				//f3ptr.read((char*)&co1,sizeof(commercial));
				cout<<"\nName | Size | Available | Shops | Facing Type | Purchase Type | Commercial Zone | Buy Price (Rs.)\n";
				f3ptr.read((char*)&co1,sizeof(commercial));
				while(!f3ptr.eof())
				{
					if((tolower(co1.get_shoplocation())=='e') && co1.available==1)
					{
						Sleep(200);
						comarr[index]=co1;
						index++;
						if(co1.available==1)
						strcpy(sr1,"YES");
						else
						strcpy(sr1,"NO");
						if(co1.get_shoplocation()=='i')
						strcpy(sr2,"Internal");
						else
						strcpy(sr2,"Front Facing");
						
						printf("\n%10d %-10s %.2f %-10s %10d %-10s %10c %10s %.2f",index,co1.pname,co1.psize,sr1,co1.get_shops(),sr2,toupper(co1.purchasetype),co1.get_zonename(),co1.baserate);//co1.pname<<co1.psize<<sr1<<co1.get_shops()<<toupper(co1.purchasetype)<<co1.get_zonename()<<co1.baserate;
					}
					f3ptr.read((char*)&co1,sizeof(commercial));
				}
					while(1)
				{
					cout<<"\nEnter desired property number: ";
					cin>>inchoice;
					if(inchoice<1 || inchoice>count)
					{
						cout<<"\nInvalid entry. Enter valid choice: ";
					}
					else
					break;
				}
				inchoice-=1;
				comarr[inchoice].displaydetails();
				cout<<"\n\nAll details now displayed. Press any key to continue...";
				getchar();
				getchar();
				}
				
			}
			else if(p1==3)
			{
				f3ptr.read((char*)&co1,sizeof(commercial));
				while(!f3ptr.eof())
				{
					if(co1.available==1)
					count++;	
					f3ptr.read((char*)&co1,sizeof(commercial));
				}
				
				if(count==0)
				{
					cout<<"\nNo available properties to match your criteria\nPress any key to continue.";
					f3ptr.close();
					f2ptr.close();
					f1ptr.close();
					getchar();
					getchar();
					return 0;
				}
				
				char proparr[count][50];
				for(int i=0;i<count;i++)
				{
					strcpy(proparr[i],"_Default");
				}
				
				f3ptr.clear();
				f3ptr.seekg(0,ios::beg);
				int index=0;
				cout<<"\nCities in which properties have been listed yet:\n\n";
				f3ptr.read((char*)&co1,sizeof(commercial));
				cout<<"S.No\tCity\n";
				while(!f3ptr.eof())
				{
					if(co1.available==1)
					{
						if(strcmp(proparr[index],"_Default")==0 && searcharr(proparr,count,co1.getCity())==0)
						{
							strcpy(proparr[index],co1.getCity());
							index++;
							cout<<index<<"\t"<<co1.getCity()<<endl;
						}					
					}
					f3ptr.read((char*)&co1,sizeof(commercial));
				}
				cout<<"\n\nEnter your choice: ";
				cin>>index;
				while(index<1 || index>count)
				{
					cout<<"\nInvalid choice. Enter valid value: ";
					cin>>index;
				}
				index-=1;
				f3ptr.clear();
				f3ptr.seekg(0,ios::beg);
				
				f3ptr.read((char*)&co1,sizeof(commercial));
				count=0;
				int i1=0;
				while(!f3ptr.eof())
				{
					if(co1.available==1 && strcmp(co1.getCity(),proparr[index])==0)
					count++;	
					f3ptr.read((char*)&co1,sizeof(commercial));
				}
				if(count==0)
				{
					cout<<"\nNo available properties to match your criteria\nPress any key to continue.";
					f3ptr.close();
					f2ptr.close();
					f1ptr.close();
					getchar();
					getchar();
					return 0;
				}
				
				commercial comarr[count];
				f3ptr.clear();
				f3ptr.seekg(0,ios::beg);
			
				cout<<"\nIndex | Name | Size | Available | Shops | Facing Type | Purchase Type | Commercial Zone | Buy Price (Rs.)\n";
				f3ptr.read((char*)&co1,sizeof(commercial));
				while(!f3ptr.eof())
				{
					if(co1.available==1 && strcmp(co1.getCity(),proparr[index])==0)
					{
						
						comarr[i1]=co1;
						i1++;
						if(co1.available==1)
						strcpy(sr1,"YES");
						else
						strcpy(sr1,"NO");
						if(co1.get_shoplocation()=='i')
						strcpy(sr2,"Internal");
						else
						strcpy(sr2,"Front Facing");
						
						printf("\n%d %-10s %.2f %-10s %10d %-10s %10c %10s %.2f",i1,co1.pname,co1.psize,sr1,co1.get_shops(),sr2,toupper(co1.purchasetype),co1.get_zonename(),co1.baserate);//co1.pname<<co1.psize<<sr1<<co1.get_shops()<<toupper(co1.purchasetype)<<co1.get_zonename()<<co1.baserate;
					}
					f3ptr.read((char*)&co1,sizeof(commercial));
				}
				cout<<"\nEnter desired property number: ";
				cin>>i1;
				while(i1<1 || i1>count)
				{
					cout<<"\nIncorrect value. Enter valid property number: ";
					cin>>i1;
				}
				i1-=1;
				comarr[i1].displaydetails();
				cout<<"\nAll property details now displayed. Press any key to continue...";
				getchar();
				getchar();
				/*char comname[50];
				cout<<"\nName | Size | Available | Shops | Facing Type | Purchase Type | Commercial Zone | Buy Price (Rs.)\n";
				f3ptr.read((char*)&co1,sizeof(commercial));
				while(!f3ptr.eof())
				{
						count++;
						if(co1.available==1)
						strcpy(sr1,"YES");
						else
						strcpy(sr1,"NO");
						if(co1.get_shoplocation()=='i')
						strcpy(sr2,"Internal");
						else
						strcpy(sr2,"Front Facing");
						
						printf("\n %-10s %.2f %-10s %10d %-10s %10c %10s %.2f",co1.pname,co1.psize,sr1,co1.get_shops(),sr2,toupper(co1.purchasetype),co1.get_zonename(),co1.baserate);//co1.pname<<co1.psize<<sr1<<co1.get_shops()<<toupper(co1.purchasetype)<<co1.get_zonename()<<co1.baserate;
					f3ptr.read((char*)&co1,sizeof(commercial));
				}
				f3ptr.clear();
				fflush(stdin);
				cout<<"\n\nEnter zone name: ";
				cin.getline(comname,50);
			
				f3ptr.seekg(0,ios::beg);
				
				cout<<"\nName | Size | Available | Shops | Facing Type | Purchase Type | Commercial Zone | Buy Price (Rs.)\n";
				f3ptr.read((char*)&co1,sizeof(commercial));
				while(!f3ptr.eof())
				{
					if(strcmp(co1.get_zonename(),comname)==0)
					{
						count++;
						if(co1.available==1)
						strcpy(sr1,"YES");
						else
						strcpy(sr1,"NO");
						if(co1.get_shoplocation()=='i')
						strcpy(sr2,"Internal");
						else
						strcpy(sr2,"Front Facing");
						
						printf("\n %-10s %.2f %-10s %10d %-10s %10c %10s %.2f",co1.pname,co1.psize,sr1,co1.get_shops(),sr2,toupper(co1.purchasetype),co1.get_zonename(),co1.baserate);//co1.pname<<co1.psize<<sr1<<co1.get_shops()<<toupper(co1.purchasetype)<<co1.get_zonename()<<co1.baserate;
					}
					f3ptr.read((char*)&co1,sizeof(commercial));
				}
				
				cout<<"\nAll available properties displayed. Press any key to continue...";
				getchar();
				getchar();*/
			}
			else if(p1==4)
			{
				int min,max;
				cout<<"\nEnter minimum and maximum buy price to filter by (min max): ";
				cin>>min>>max;
				while((min>max) || (min<=0) || (max<=0))
				{
					cout<<"\nInvalid entry.\n\n*Min must be greater than Max\n*Min and Max must be positive\nEnter minimum and maximum buy price to filter by (min max):  ";
					cin>>min>>max;
				}
				f3ptr.read((char*)&co1,sizeof(commercial));
				while(!f3ptr.eof())
				{
					if((co1.baserate>=min && co1.baserate<=max) && co1.available==1)
					count++;
					f3ptr.read((char*)&co1,sizeof(commercial));
				}
				if(count==0)
				{
					cout<<"\n\nNo available properties that match your criteria. Press any key to continue.\n\n";
					f3ptr.close();
					f2ptr.close();
					f1ptr.close();
					getchar();
					getchar();
					return 1;
				}
				commercial comarr[count];
				cout<<"\n\nNow displaying properties:\n\nName |\t Size |\t Available |\t Shops |\t Facing Type |\t Purchase Type |\t Commercial Zone |\t Buy Price (Rs.) |\n";
				f3ptr.clear();
				f3ptr.seekg(0,ios::beg);
				//cout<<"\nName | Size | Available | Shops | Facing Type | Purchase Type | Commercial Zone | Buy Price (Rs.)\n";
				f3ptr.read((char*)&co1,sizeof(commercial));
				while(!f3ptr.eof())
				{
					if((co1.baserate>=min && co1.baserate<=max) && co1.available==1)
					{
						Sleep(200);
						comarr[index]=co1;
						index++;
						if(co1.available==1)
						strcpy(sr1,"YES");
						else
						strcpy(sr1,"NO");
						if(co1.get_shoplocation()=='i')
						strcpy(sr2,"Internal");
						else
						strcpy(sr2,"Front Facing");
						
						printf("\n%10d %-10s %.2f %-10s %10d %-10s %10c %10s %.2f",index,co1.pname,co1.psize,sr1,co1.get_shops(),sr2,toupper(co1.purchasetype),co1.get_zonename(),co1.baserate);//co1.pname<<co1.psize<<sr1<<co1.get_shops()<<toupper(co1.purchasetype)<<co1.get_zonename()<<co1.baserate;
					}
					f3ptr.read((char*)&co1,sizeof(commercial));
				}
				while(1)
				{
					cout<<"\nEnter desired property number: ";
					cin>>inchoice;
					if(inchoice<1 || inchoice>count)
					{
						cout<<"\nInvalid entry. Enter valid choice: ";
					}
					else
					break;
				}
					inchoice-=1;
					comarr[inchoice].displaydetails();
					cout<<"\n\nAll details now displayed. Press any key to continue...";
					getchar();
					getchar();
			
			}
		}
		else
		{
			//houses and flats
			int rchoice;
			cout<<"\nEnter:\n1. Houses\n2. Flats: ";
			cin>>rchoice;
			while(rchoice!=1 && rchoice!=2)
			{
				cout<<"\nInvalid. Enter:\n1. Houses\n2. Flats: ";
				cin>>rchoice;
			}
			if(rchoice==1)
			{
				house ho1;
				cout<<"\n\nVIEW MENU\n\nFilter by:\n1. Number of Rooms\n2. Purchase Type\n3. House Type\n4. Price\n5. Location\nEnter your choice: ";
				cin>>p1;
				while(!(p1>=1 && p1<=5))
				{
					cout<<"\nEnter valid choice: ";
					cin>>p1;
				}
				if(p1==1)
				{
				int min,max;
				cout<<"\nEnter minimum and maximum number of desired rooms (min max): ";
				cin>>min>>max;
				while((min>max) || (min<=0) || (max<=0))
				{
					cout<<"\nInvalid entry. Enter minimum and maximum number of desired rooms (min max): ";
					cin>>min>>max;
				}
				
				f1ptr.read((char*)&ho1,sizeof(house));
				while(!f1ptr.eof())
				{
					if((ho1.rooms>=min && ho1.rooms<=max) && ho1.available==1)
					count++;
					f1ptr.read((char*)&ho1,sizeof(house));
				}
				if(count==0)
				{
					cout<<"\n\nNo available properties that match your criteria. Press any key to continue.\n\n";
					f3ptr.close();
					f2ptr.close();
					f1ptr.close();
					getchar();
					getchar();
					return 1;
				}
				house comarr[count];
				f1ptr.clear();
				f1ptr.seekg(0,ios::beg);
				cout<<"\nName | Size (Sq. Guz) | Available | Rooms | House Type | Purchase Type |  Floors | Furnished | Buy Price (Rs.)\n";
				f1ptr.read((char*)&ho1,sizeof(house));
				while(!f1ptr.eof())
				{
					if((ho1.rooms>=min && ho1.rooms<=max) && ho1.available==1)
					{
						comarr[index]=ho1;
						index++;
						if(ho1.available==1)
						strcpy(sr1,"YES");
						else
						strcpy(sr1,"NO");
						if(ho1.furnished==1)
						strcpy(sr2,"YES");
						else
						strcpy(sr2,"NO");
						
						printf("\n%10d %-10s %.2f %-10s %10d %-10s %10c %10d %-10s %.2f",index,ho1.pname,ho1.psize,sr1,ho1.rooms,ho1.get_housetype(),toupper(ho1.purchasetype),ho1.floors,sr2,ho1.baserate);//co1.pname<<co1.psize<<sr1<<co1.get_shops()<<toupper(co1.purchasetype)<<co1.get_zonename()<<co1.baserate;
					}
					f1ptr.read((char*)&ho1,sizeof(house));
				}
				while(1)
				{
					cout<<"\nEnter desired property number: ";
					cin>>inchoice;
					if(inchoice<1 || inchoice>count)
					{
						cout<<"\nInvalid entry. Enter valid choice: ";
					}
					else
					break;
				}
				inchoice-=1;
				comarr[inchoice].displaydetails();
				cout<<"\n\nAll details now displayed. Press any key to continue...";
				getchar();
				getchar();
				}
				else if(p1==2)
				{
					int ch;
					cout<<"\nSelect Purchase Type:\n1. Buy\n2. Rent: ";
					cin>>ch;
					while(!(ch>=1 && ch<=2))
					{
						cout<<"\nInvalid.\nSelect Purchase Type:\n1. Buy\n2. Rent: ";
						cin>>ch;
					}
					if(ch==1)
					{
						f1ptr.read((char*)&ho1,sizeof(house));
						while(!f1ptr.eof())
						{
							if((tolower(ho1.purchasetype)=='b') && ho1.available==1)
							count++;
							f1ptr.read((char*)&ho1,sizeof(house));
						}
					if(count==0)
					{
						cout<<"\n\nNo available properties that match your criteria. Press any key to continue.\n\n";
						f3ptr.close();
						f2ptr.close();
						f1ptr.close();
						getchar();
						getchar();
						return 1;
					}
						house comarr[count];
						f1ptr.clear();
						f1ptr.seekg(0,ios::beg);
						cout<<"\nName | Size (Sq. Guz) | Available | Rooms | House Type | Purchase Type |  Floors | Furnished | Buy Price (Rs.)\n";
						f1ptr.read((char*)&ho1,sizeof(house));
						while(!f1ptr.eof())
						{
							if((tolower(ho1.purchasetype)=='b') && ho1.available==1)
							{
								comarr[index]=ho1;
								index++;
								if(ho1.available==1)
								strcpy(sr1,"YES");
								else
								strcpy(sr1,"NO");
								if(ho1.furnished==1)
								strcpy(sr2,"YES");
								else
								strcpy(sr2,"NO");
						
								printf("\n%10d %-10s %.2f %-10s %10d %-10s %10c %10d %-10s %.2f",index,ho1.pname,ho1.psize,sr1,ho1.rooms,ho1.get_housetype(),toupper(ho1.purchasetype),ho1.floors,sr2,ho1.baserate);//co1.pname<<co1.psize<<sr1<<co1.get_shops()<<toupper(co1.purchasetype)<<co1.get_zonename()<<co1.baserate;
							}
							f1ptr.read((char*)&ho1,sizeof(house));
						}
					while(1)
					{
						cout<<"\nEnter desired property number: ";
						cin>>inchoice;
						if(inchoice<1 || inchoice>count)
						{
							cout<<"\nInvalid entry. Enter valid choice: ";
						}
						else
						break;
					}
				inchoice-=1;
				comarr[inchoice].displaydetails();
				cout<<"\n\nAll details now displayed. Press any key to continue...";
				getchar();
				getchar();
					}
					else
					{
							f1ptr.read((char*)&ho1,sizeof(house));
						while(!f1ptr.eof())
						{
							if((tolower(ho1.purchasetype)=='r') && ho1.available==1)
							count++;
							f1ptr.read((char*)&ho1,sizeof(house));
						}
					if(count==0)
					{
						cout<<"\n\nNo available properties that match your criteria. Press any key to continue.\n\n";
						f3ptr.close();
						f2ptr.close();
						f1ptr.close();
						getchar();
						getchar();
						return 1;
					}
						house comarr[count];
						f1ptr.clear();
						f1ptr.seekg(0,ios::beg);
							cout<<"\nName | Size (Sq. Guz) | Available | Rooms | House Type | Purchase Type |  Floors | Furnished | Buy Price (Rs.)\n";
						f1ptr.read((char*)&ho1,sizeof(house));
						while(!f1ptr.eof())
						{
							if((tolower(ho1.purchasetype)=='r') && ho1.available==1)
							{
								comarr[index]=ho1;
								index++;
								if(ho1.available==1)
								strcpy(sr1,"YES");
								else
								strcpy(sr1,"NO");
								if(ho1.furnished==1)
								strcpy(sr2,"YES");
								else
								strcpy(sr2,"NO");
						
								printf("\n%10d %-10s %.2f %-10s %10d %-10s %10c %10d %-10s %.2f",index,ho1.pname,ho1.psize,sr1,ho1.rooms,ho1.get_housetype(),toupper(ho1.purchasetype),ho1.floors,sr2,ho1.baserate);//co1.pname<<co1.psize<<sr1<<co1.get_shops()<<toupper(co1.purchasetype)<<co1.get_zonename()<<co1.baserate;
							}
							f1ptr.read((char*)&ho1,sizeof(house));
						}
						while(1)
						{
							cout<<"\nEnter desired property number: ";
							cin>>inchoice;
							if(inchoice<1 || inchoice>count)
							{
								cout<<"\nInvalid entry. Enter valid choice: ";
							}
							else
							break;
						}
						inchoice-=1;
						comarr[inchoice].displaydetails();
						cout<<"\n\nAll details now displayed. Press any key to continue...";
						getchar();
						getchar();
					}
				}
				else if(p1==3)
				{
					int ch;
					cout<<"\nSelect House Type:\n1. Villa\n2. Portion\n3. Penthouse: ";
					cin>>ch;
					while(!(ch>=1 && ch<=3))
					{
						cout<<"\nInvalid.\nSelect House Type:\n1. Villa\n2. Portion\n3. Penthouse: ";
						cin>>ch;
					}
					cout<<"\nName | Size (Sq. Guz) | Available | Rooms | House Type | Purchase Type |  Floors | Furnished | Buy Price (Rs.)\n";
					if(ch==1)
					{
						f1ptr.read((char*)&ho1,sizeof(house));
						while(!f1ptr.eof())
						{
							if((strcmp(ho1.get_housetype(),"Villa")==0) && ho1.available==1)
							count++;
							f1ptr.read((char*)&ho1,sizeof(house));
						}
						if(count==0)
						{
							cout<<"\n\nNo available properties that match your criteria. Press any key to continue.\n\n";
							f3ptr.close();
							f2ptr.close();
							f1ptr.close();
							getchar();
							getchar();
							return 1;
						}
						house comarr[count];
						f1ptr.clear();
						f1ptr.seekg(0,ios::beg);
						f1ptr.read((char*)&ho1,sizeof(house));
						while(!f1ptr.eof())
						{
							if((strcmp(ho1.get_housetype(),"Villa")==0) && ho1.available==1)
							{
								comarr[index]=ho1;
								index++;
								if(ho1.available==1)
								strcpy(sr1,"YES");
								else
								strcpy(sr1,"NO");
								if(ho1.furnished==1)
								strcpy(sr2,"YES");
								else
								strcpy(sr2,"NO");
						
								printf("\n%10d %-10s %.2f %-10s %10d %-10s %10c %10d %-10s %.2f",index,ho1.pname,ho1.psize,sr1,ho1.rooms,ho1.get_housetype(),toupper(ho1.purchasetype),ho1.floors,sr2,ho1.baserate);//co1.pname<<co1.psize<<sr1<<co1.get_shops()<<toupper(co1.purchasetype)<<co1.get_zonename()<<co1.baserate;
							}
							f1ptr.read((char*)&ho1,sizeof(house));
						}
							while(1)
					{
						cout<<"\nEnter desired property number: ";
						cin>>inchoice;
						if(inchoice<1 || inchoice>count)
						{
							cout<<"\nInvalid entry. Enter valid choice: ";
						}
						else
						break;
					}
					inchoice-=1;
					comarr[inchoice].displaydetails();
					cout<<"\n\nAll details now displayed. Press any key to continue...";
					getchar();
					getchar();
					}
					else if(ch==2)
					{
						f1ptr.read((char*)&ho1,sizeof(house));
						while(!f1ptr.eof())
						{
							if((strcmp(ho1.get_housetype(),"Portion")==0) && ho1.available==1)
							count++;
							f1ptr.read((char*)&ho1,sizeof(house));
						}
						if(count==0)
						{
							cout<<"\n\nNo available properties that match your criteria. Press any key to continue.\n\n";
							f3ptr.close();
							f2ptr.close();
							f1ptr.close();
							getchar();
							getchar();
							return 1;
						}
						house comarr[count];
						f1ptr.clear();
						f1ptr.seekg(0,ios::beg);
						f1ptr.read((char*)&ho1,sizeof(house));
						while(!f1ptr.eof())
						{
							if((strcmp(ho1.get_housetype(),"Portion")==0) && ho1.available==1)
							{
								comarr[index]=ho1;
								index++;
								if(ho1.available==1)
								strcpy(sr1,"YES");
								else
								strcpy(sr1,"NO");
								if(ho1.furnished==1)
								strcpy(sr2,"YES");
								else
								strcpy(sr2,"NO");
						
								printf("\n%10d %-10s %.2f %-10s %10d %-10s %10c %10d %-10s %.2f",index,ho1.pname,ho1.psize,sr1,ho1.rooms,ho1.get_housetype(),toupper(ho1.purchasetype),ho1.floors,sr2,ho1.baserate);//co1.pname<<co1.psize<<sr1<<co1.get_shops()<<toupper(co1.purchasetype)<<co1.get_zonename()<<co1.baserate;
							}
							f1ptr.read((char*)&ho1,sizeof(house));
						}
							while(1)
					{
						cout<<"\nEnter desired property number: ";
						cin>>inchoice;
						if(inchoice<1 || inchoice>count)
						{
							cout<<"\nInvalid entry. Enter valid choice: ";
						}
						else
						break;
					}
					inchoice-=1;
					comarr[inchoice].displaydetails();
					cout<<"\n\nAll details now displayed. Press any key to continue...";
					getchar();
					getchar();
					}
					else if(ch==3)
					{
						f1ptr.read((char*)&ho1,sizeof(house));
						while(!f1ptr.eof())
						{
							if((strcmp(ho1.get_housetype(),"Penthouse")==0) && ho1.available==1)
							count++;
							f1ptr.read((char*)&ho1,sizeof(house));
						}
						if(count==0)
						{
							cout<<"\n\nNo available properties that match your criteria. Press any key to continue.\n\n";
							f3ptr.close();
							f2ptr.close();
							f1ptr.close();
							getchar();
							getchar();
							return 1;
						}
						house comarr[count];
						f1ptr.clear();
						f1ptr.seekg(0,ios::beg);
						f1ptr.read((char*)&ho1,sizeof(house));
						while(!f1ptr.eof())
						{
							if((strcmp(ho1.get_housetype(),"Penthouse")==0) && ho1.available==1)
							{
								comarr[index]=ho1;
								index++;
								if(ho1.available==1)
								strcpy(sr1,"YES");
								else
								strcpy(sr1,"NO");
								if(ho1.furnished==1)
								strcpy(sr2,"YES");
								else
								strcpy(sr2,"NO");
						
								printf("\n%10d %-10s %.2f %-10s %10d %-10s %10c %10d %-10s %.2f",index,ho1.pname,ho1.psize,sr1,ho1.rooms,ho1.get_housetype(),toupper(ho1.purchasetype),ho1.floors,sr2,ho1.baserate);//co1.pname<<co1.psize<<sr1<<co1.get_shops()<<toupper(co1.purchasetype)<<co1.get_zonename()<<co1.baserate;
							}
							f1ptr.read((char*)&ho1,sizeof(house));
						}
							while(1)
					{
						cout<<"\nEnter desired property number: ";
						cin>>inchoice;
						if(inchoice<1 || inchoice>count)
						{
							cout<<"\nInvalid entry. Enter valid choice: ";
						}
						else
						break;
					}
					inchoice-=1;
					comarr[inchoice].displaydetails();
					cout<<"\n\nAll details now displayed. Press any key to continue...";
					getchar();
					getchar();
					}
				
				}
				else if(p1==4)
				{
						int min,max;
				cout<<"\nEnter minimum and maximum price to filter by (min max): ";
				cin>>min>>max;
				while((min>max) || (min<=0) || (max<=0))
				{
					cout<<"\nInvalid entry. Enter minimum and maximum price to filter by (min max): ";
					cin>>min>>max;
				}
				f1ptr.read((char*)&ho1,sizeof(house));
				while(!f1ptr.eof())
				{
					if((ho1.rooms>=min && ho1.rooms<=max) && ho1.available==1)
					count++;
					f1ptr.read((char*)&ho1,sizeof(house));
				}
				if(count==0)
				{
					cout<<"\n\nNo available properties that match your criteria. Press any key to continue.\n\n";
					f3ptr.close();
					f2ptr.close();
					f1ptr.close();
					getchar();
					getchar();
					return 1;
				}
				house comarr[count];
				f1ptr.clear();
				f1ptr.seekg(0,ios::beg);
				cout<<"\nName | Size (Sq. Guz) | Available | Rooms | House Type | Purchase Type |  Floors | Furnished | Buy Price (Rs.)\n";
				f1ptr.read((char*)&ho1,sizeof(house));
				while(!f1ptr.eof())
				{
					if((ho1.baserate>=min && ho1.baserate<=max) && ho1.available==1)
					{
						comarr[index]=ho1;
						index++;
						if(ho1.available==1)
						strcpy(sr1,"YES");
						else
						strcpy(sr1,"NO");
						if(ho1.furnished==1)
						strcpy(sr2,"YES");
						else
						strcpy(sr2,"NO");
						
						printf("\n%-10d %-10s %.2f %-10s %10d %-10s %10c %10d %-10s %.2f",index,ho1.pname,ho1.psize,sr1,ho1.rooms,ho1.get_housetype(),toupper(ho1.purchasetype),ho1.floors,sr2,ho1.baserate);//co1.pname<<co1.psize<<sr1<<co1.get_shops()<<toupper(co1.purchasetype)<<co1.get_zonename()<<co1.baserate;
					}
					f1ptr.read((char*)&ho1,sizeof(house));
				}
					while(1)
					{
						cout<<"\nEnter desired property number: ";
						cin>>inchoice;
						if(inchoice<1 || inchoice>count)
						{
							cout<<"\nInvalid entry. Enter valid choice: ";
						}
						else
						break;
					}
					inchoice-=1;
					comarr[inchoice].displaydetails();
					cout<<"\n\nAll details now displayed. Press any key to continue...";
					getchar();
					getchar();
					}
					else if(p1==5)
					{
						f1ptr.read((char*)&ho1,sizeof(house));
					while(!f1ptr.eof())
					{
						if(ho1.available==1)
						count++;	
						f1ptr.read((char*)&ho1,sizeof(house));
					}
					
					char proparr[count][50];
					for(int i=0;i<count;i++)
					{
						strcpy(proparr[i],"_Default");
					}
				
					f1ptr.clear();
					f1ptr.seekg(0,ios::beg);
					int index=0;
					cout<<"\nCities in which properties have been listed yet:\n\n";
					f1ptr.read((char*)&ho1,sizeof(house));
					cout<<"S.No\tCity\n";
					while(!f1ptr.eof())
					{
						if(ho1.available==1)
						{
							if(strcmp(proparr[index],"_Default")==0 && searcharr(proparr,count,ho1.getCity())==0)
							{
								strcpy(proparr[index],ho1.getCity());
								index++;
								cout<<index<<"\t"<<ho1.getCity()<<endl;
							}					
						}
						f1ptr.read((char*)&ho1,sizeof(house));
					}
					cout<<"\n\nEnter your choice: ";
					cin>>index;
					while(index<1 || index>count)
					{
						cout<<"\nInvalid choice. Enter valid value: ";
						cin>>index;
					}
					index-=1;
					f1ptr.clear();
					f1ptr.seekg(0,ios::beg);
					
					f1ptr.read((char*)&ho1,sizeof(house));
					count=0;
					int i1=0;
					while(!f1ptr.eof())
					{
						if(ho1.available==1 && strcmp(ho1.getCity(),proparr[index])==0)
						count++;	
						f1ptr.read((char*)&ho1,sizeof(house));
					}
					if(count==0)
					{
						cout<<"\nNo available properties to match your criteria\nPress any key to continue.";
						f3ptr.close();
						f2ptr.close();
						f1ptr.close();
						getchar();
						getchar();
						return 0;
					}
				
					house comarr[count];
					f1ptr.clear();
					f1ptr.seekg(0,ios::beg);
			
					cout<<"\nIndex | Name | Size (Sq. Guz) | Available | Rooms | House Type | Purchase Type |  Floors | Furnished | Buy Price (Rs.)\n";
					f1ptr.read((char*)&ho1,sizeof(house));
					while(!f1ptr.eof())
					{
						if(ho1.available==1 && strcmp(ho1.getCity(),proparr[index])==0)
						{
							
							comarr[i1]=ho1;
							i1++;
							if(ho1.available==1)
							strcpy(sr1,"YES");
							else
							strcpy(sr1,"NO");
							if(ho1.furnished==1)
							strcpy(sr2,"YES");
							else
							strcpy(sr2,"NO");
						
							printf("\n%-10d %-10s %.2f %-10s %10d %-10s %10c %10d %-10s %.2f",i1,ho1.pname,ho1.psize,sr1,ho1.rooms,ho1.get_housetype(),toupper(ho1.purchasetype),ho1.floors,sr2,ho1.baserate);//co1.pname<<co1.psize<<sr1<<co1.get_shops()<<toupper(co1.purchasetype)<<co1.get_zonename()<<co1.baserate;
						}
						f1ptr.read((char*)&ho1,sizeof(house));
					}
					cout<<"\nEnter desired property number: ";
					cin>>i1;
					while(i1<1 || i1>count)
					{
						cout<<"\nIncorrect value. Enter valid property number: ";
						cin>>i1;
					}
					i1-=1;
					comarr[i1].displaydetails();
					cout<<"\nAll property details now displayed. Press any key to continue...";
					getchar();
					getchar();
					}
			}
			else
			{
				char sr3[20],sr4[20];
				flat fo1;
				cout<<"\n\nVIEW MENU\n\nFilter by:\n1. Parking facility\n2. Purchase Type\n3. Elevator service\n4. Price\n5. Location\nEnter your choice: ";
				cin>>p1;
				while(!(p1>=1 && p1<=5))
				{
					cout<<"\nEnter valid choice: ";
					cin>>p1;
				}	
				if(p1==1)
				{
					f2ptr.read((char*)&fo1,sizeof(flat));
					while(!f2ptr.eof())
					{
						if((fo1.get_parking()==1) && fo1.available==1)
						count++;
						f2ptr.read((char*)&fo1,sizeof(flat));
					}
					if(count==0)
					{
						cout<<"\nNo available properties to match your criteria\nPress any key to continue.";
						f3ptr.close();
						f2ptr.close();
						f1ptr.close();
						getchar();
						getchar();
						return 0;
					}
				
					flat comarr[count];
					index=0;
					f2ptr.clear();
					f2ptr.seekg(0,ios::beg);
					cout<<"\nName | Size (Sq. Guz) | Available | Rooms | Parking | Purchase Type |  Elevator | Furnished | Buy Price (Rs.)\n";
					f2ptr.read((char*)&fo1,sizeof(flat));
					
					while(!f2ptr.eof())
					{
					if((fo1.get_parking()==1) && fo1.available==1)
					{
						comarr[index]=fo1;
						index++;
						if(fo1.available==1)
						strcpy(sr1,"YES");
						else
						strcpy(sr1,"NO");
						if(fo1.furnished==1)
						strcpy(sr2,"YES");
						else
						strcpy(sr2,"NO");
						if(fo1.get_parking()==1)
						strcpy(sr3,"YES");
						else
						strcpy(sr3,"NO");
						if(fo1.get_elevator()==1)
						strcpy(sr4,"YES");
						else
						strcpy(sr4,"NO");
						
						printf("\n%-10d %-10s %.2f %-10s %10d %-10s %10c %-10s %-10s %.2f",index,fo1.pname,fo1.psize,sr1,fo1.rooms,sr3,toupper(fo1.purchasetype),sr4,sr2,fo1.baserate);//co1.pname<<co1.psize<<sr1<<co1.get_shops()<<toupper(co1.purchasetype)<<co1.get_zonename()<<co1.baserate;
					}
						f2ptr.read((char*)&fo1,sizeof(flat));
					}
					cout<<"\n\nEnter desired property number: ";
					cin>>index;
					while(index<1 || index>count)
					{
						cout<<"\nIncorrect entry. Enter valid choice: ";
						cin>>index;
					}
					index-=1;
					comarr[index].displaydetails();
					cout<<"\nAll property details displayed. Press any key to continue...";
					getchar();
					getchar();
				}
				else if(p1==2)
				{
					
					int ch;
					cout<<"\nSelect Purchase Type:\n1. Buy\n2. Rent: ";
					cin>>ch;
					while(!(ch>=1 && ch<=2))
					{
						cout<<"\nInvalid.\nSelect Purchase Type:\n1. Buy\n2. Rent: ";
						cin>>ch;
					}
					if(ch==1)
					{
					f2ptr.read((char*)&fo1,sizeof(flat));
					while(!f2ptr.eof())
					{
						if((tolower(fo1.purchasetype)=='b') && fo1.available==1)
						count++;
						f2ptr.read((char*)&fo1,sizeof(flat));
					}
					if(count==0)
					{
						cout<<"\nNo available properties to match your criteria\nPress any key to continue.";
						f3ptr.close();
						f2ptr.close();
						f1ptr.close();
						getchar();
						getchar();
						return 0;
					}
				
					flat comarr[count];
					index=0;
					f2ptr.clear();
					f2ptr.seekg(0,ios::beg);
					cout<<"\nName | Size (Sq. Guz) | Available | Rooms | Parking | Purchase Type |  Elevator | Furnished | Buy Price (Rs.)\n";
					f2ptr.read((char*)&fo1,sizeof(flat));
					while(!f2ptr.eof())
					{
					if((tolower(fo1.purchasetype)=='b') && fo1.available==1)
					{
						comarr[index]=fo1;
						index++;
						if(fo1.available==1)
						strcpy(sr1,"YES");
						else
						strcpy(sr1,"NO");
						if(fo1.furnished==1)
						strcpy(sr2,"YES");
						else
						strcpy(sr2,"NO");
						if(fo1.get_parking()==1)
						strcpy(sr3,"YES");
						else
						strcpy(sr3,"NO");
						if(fo1.get_elevator()==1)
						strcpy(sr4,"YES");
						else
						strcpy(sr4,"NO");
						
						printf("\n%-10d %-10s %.2f %-10s %10d %-10s %10c %-10s %-10s %.2f",index,fo1.pname,fo1.psize,sr1,fo1.rooms,sr3,toupper(fo1.purchasetype),sr4,sr2,fo1.baserate);//co1.pname<<co1.psize<<sr1<<co1.get_shops()<<toupper(co1.purchasetype)<<co1.get_zonename()<<co1.baserate;
					}
						f2ptr.read((char*)&fo1,sizeof(flat));
					}
					f2ptr.clear();
					cout<<"\n\nEnter desired property number: ";
					cin>>index;
					while(index<1 || index>count)
					{
						cout<<"\nIncorrect entry. Enter valid choice: ";
						cin>>index;
					}
					index-=1;
					comarr[index].displaydetails();
					cout<<"\nAll property details displayed. Press any key to continue...";
					getchar();
					getchar();
					}
					else if(ch==2)
					{
					f2ptr.read((char*)&fo1,sizeof(flat));
					while(!f2ptr.eof())
					{
						if((tolower(fo1.purchasetype)=='r') && fo1.available==1)
						count++;
						f2ptr.read((char*)&fo1,sizeof(flat));
					}
					if(count==0)
					{
						cout<<"\nNo available properties to match your criteria\nPress any key to continue.";
						f3ptr.close();
						f2ptr.close();
						f1ptr.close();
						getchar();
						getchar();
						return 0;
					}
				
					flat comarr[count];
					index=0;
					f2ptr.clear();
					f2ptr.seekg(0,ios::beg);
					cout<<"\nName | Size (Sq. Guz) | Available | Rooms | Parking | Purchase Type |  Elevator | Furnished | Buy Price (Rs.)\n";
					f2ptr.read((char*)&fo1,sizeof(flat));
					while(!f2ptr.eof())
					{
					if((tolower(fo1.purchasetype)=='r') && fo1.available==1)
					{
						comarr[index]=fo1;
						index++;
						if(fo1.available==1)
						strcpy(sr1,"YES");
						else
						strcpy(sr1,"NO");
						if(fo1.furnished==1)
						strcpy(sr2,"YES");
						else
						strcpy(sr2,"NO");
						if(fo1.get_parking()==1)
						strcpy(sr3,"YES");
						else
						strcpy(sr3,"NO");
						if(fo1.get_elevator()==1)
						strcpy(sr4,"YES");
						else
						strcpy(sr4,"NO");
						
						printf("\n%-10d %-10s %.2f %-10s %10d %-10s %10c %-10s %-10s %.2f",index,fo1.pname,fo1.psize,sr1,fo1.rooms,sr3,toupper(fo1.purchasetype),sr4,sr2,fo1.baserate);//co1.pname<<co1.psize<<sr1<<co1.get_shops()<<toupper(co1.purchasetype)<<co1.get_zonename()<<co1.baserate;
					}
						f2ptr.read((char*)&fo1,sizeof(flat));
					}
					f2ptr.clear();
					cout<<"\n\nEnter desired property number: ";
					cin>>index;
					while(index<1 || index>count)
					{
						cout<<"\nIncorrect entry. Enter valid choice: ";
						cin>>index;
					}
					index-=1;
					comarr[index].displaydetails();
					cout<<"\nAll property details displayed. Press any key to continue...";
					getchar();
					getchar();
					}
					
				}
				else if(p1==3)
				{
					f2ptr.read((char*)&fo1,sizeof(flat));
					while(!f2ptr.eof())
					{
						if((fo1.get_elevator()==1) && fo1.available==1)
						count++;
						f2ptr.read((char*)&fo1,sizeof(flat));
					}
					if(count==0)
					{
						cout<<"\nNo available properties to match your criteria\nPress any key to continue.";
						f3ptr.close();
						f2ptr.close();
						f1ptr.close();
						getchar();
						getchar();
						return 0;
					}
				
					flat comarr[count];
					index=0;
					f2ptr.clear();
					f2ptr.seekg(0,ios::beg);
					cout<<"\nName | Size (Sq. Guz) | Available | Rooms | Parking | Purchase Type |  Elevator | Furnished | Buy Price (Rs.)\n";
					f2ptr.read((char*)&fo1,sizeof(flat));
					while(!f2ptr.eof())
					{
					if((fo1.get_elevator()==1) && fo1.available==1)
					{
						comarr[index]=fo1;
						index++;
						if(fo1.available==1)
						strcpy(sr1,"YES");
						else
						strcpy(sr1,"NO");
						if(fo1.furnished==1)
						strcpy(sr2,"YES");
						else
						strcpy(sr2,"NO");
						if(fo1.get_parking()==1)
						strcpy(sr3,"YES");
						else
						strcpy(sr3,"NO");
						if(fo1.get_elevator()==1)
						strcpy(sr4,"YES");
						else
						strcpy(sr4,"NO");
						
						printf("\n%-10d %-10s %.2f %-10s %10d %-10s %10c %-10s %-10s %.2f",index,fo1.pname,fo1.psize,sr1,fo1.rooms,sr3,toupper(fo1.purchasetype),sr4,sr2,fo1.baserate);//co1.pname<<co1.psize<<sr1<<co1.get_shops()<<toupper(co1.purchasetype)<<co1.get_zonename()<<co1.baserate;
					}
						f2ptr.read((char*)&fo1,sizeof(flat));
					}
					f2ptr.clear();
					cout<<"\n\nEnter desired property number: ";
					cin>>index;
					while(index<1 || index>count)
					{
						cout<<"\nIncorrect entry. Enter valid choice: ";
						cin>>index;
					}
					index-=1;
					comarr[index].displaydetails();
					cout<<"\nAll property details displayed. Press any key to continue...";
					getchar();
					getchar();
				}
				else if(p1==4)
				{
				int min,max;
				cout<<"\nEnter minimum and maximum price to filter by (min max): ";
				cin>>min>>max;
				while((min>max) || (min<=0) || (max<=0))
				{
					cout<<"\nInvalid entry. Enter minimum and maximum price to filter by (min max): ";
					cin>>min>>max;
				}
				
				f2ptr.read((char*)&fo1,sizeof(flat));
					while(!f2ptr.eof())
					{
						if((fo1.baserate>=min && fo1.baserate<=max) && fo1.available==1)
						count++;
						f2ptr.read((char*)&fo1,sizeof(flat));
					}
					if(count==0)
					{
						cout<<"\nNo available properties to match your criteria\nPress any key to continue.";
						f3ptr.close();
						f2ptr.close();
						f1ptr.close();
						getchar();
						getchar();
						return 0;
					}
				
					flat comarr[count];
					index=0;
					f2ptr.clear();
					f2ptr.seekg(0,ios::beg);
					cout<<"\nName | Size (Sq. Guz) | Available | Rooms | Parking | Purchase Type |  Elevator | Furnished | Buy Price (Rs.)\n";
					f2ptr.read((char*)&fo1,sizeof(flat));
				while(!f2ptr.eof())
				{
					if((fo1.baserate>=min && fo1.baserate<=max) && fo1.available==1)
					{
						comarr[index]=fo1;
						index++;
						if(fo1.available==1)
						strcpy(sr1,"YES");
						else
						strcpy(sr1,"NO");
						if(fo1.furnished==1)
						strcpy(sr2,"YES");
						else
						strcpy(sr2,"NO");
						if(fo1.get_parking()==1)
						strcpy(sr3,"YES");
						else
						strcpy(sr3,"NO");
						if(fo1.get_elevator()==1)
						strcpy(sr4,"YES");
						else
						strcpy(sr4,"NO");
						
						printf("\n%-10d %-10s %.2f %-10s %10d %-10s %10c %-10s %-10s %.2f",index,fo1.pname,fo1.psize,sr1,fo1.rooms,sr3,toupper(fo1.purchasetype),sr4,sr2,fo1.baserate);//co1.pname<<co1.psize<<sr1<<co1.get_shops()<<toupper(co1.purchasetype)<<co1.get_zonename()<<co1.baserate;
					}
					f2ptr.read((char*)&fo1,sizeof(flat));
				}
				f2ptr.clear();
					cout<<"\n\nEnter desired property number: ";
					cin>>index;
					while(index<1 || index>count)
					{
						cout<<"\nIncorrect entry. Enter valid choice: ";
						cin>>index;
					}
					index-=1;
					comarr[index].displaydetails();
					cout<<"\nAll property details displayed. Press any key to continue...";
					getchar();
					getchar();
				}
				else if(p1==5)
					{
						f2ptr.read((char*)&fo1,sizeof(flat));
					while(!f2ptr.eof())
					{
						if(fo1.available==1)
						count++;	
						f2ptr.read((char*)&fo1,sizeof(flat));
					}
					
					char proparr[count][50];
					for(int i=0;i<count;i++)
					{
						strcpy(proparr[i],"_Default");
					}
				
					f2ptr.clear();
					f2ptr.seekg(0,ios::beg);
					int index=0;
					cout<<"\nCities in which properties have been listed yet:\n\n";
					f2ptr.read((char*)&fo1,sizeof(flat));
					cout<<"S.No\tCity\n";
					while(!f2ptr.eof())
					{
						if(fo1.available==1)
						{
							if(strcmp(proparr[index],"_Default")==0 && searcharr(proparr,count,fo1.getCity())==0)
							{
								strcpy(proparr[index],fo1.getCity());
								index++;
								cout<<index<<"\t"<<fo1.getCity()<<endl;
							}					
						}
					f2ptr.read((char*)&fo1,sizeof(flat));
					}
					cout<<"\n\nEnter your choice: ";
					cin>>index;
					while(index<1 || index>count)
					{
						cout<<"\nInvalid choice. Enter valid value: ";
						cin>>index;
					}
					index-=1;
					f2ptr.clear();
					f2ptr.seekg(0,ios::beg);
					
					f2ptr.read((char*)&fo1,sizeof(flat));
					count=0;
					int i1=0;
					while(!f2ptr.eof())
					{
						if(fo1.available==1 && strcmp(fo1.getCity(),proparr[index])==0)
						count++;	
						f2ptr.read((char*)&fo1,sizeof(flat));
					}
					if(count==0)
					{
						cout<<"\nNo available properties to match your criteria\nPress any key to continue.";
						f3ptr.close();
						f2ptr.close();
						f1ptr.close();
						getchar();
						getchar();
						return 0;
					}
				
					flat comarr[count];
					f2ptr.clear();
					f2ptr.seekg(0,ios::beg);
			
					cout<<"\nIndex | Name | Size (Sq. Guz) | Available | Rooms | Parking | Purchase Type |  Elevator | Furnished | Buy Price (Rs.)\n";
					f2ptr.read((char*)&fo1,sizeof(flat));
					while(!f2ptr.eof())
					{
						if(fo1.available==1 && strcmp(fo1.getCity(),proparr[index])==0)
						{
							
							comarr[i1]=fo1;
							i1++;
							if(fo1.available==1)
							strcpy(sr1,"YES");
							else
							strcpy(sr1,"NO");
							if(fo1.furnished==1)
							strcpy(sr2,"YES");
							else
							strcpy(sr2,"NO");
							if(fo1.get_parking()==1)
							strcpy(sr3,"YES");
							else
							strcpy(sr3,"NO");
							if(fo1.get_elevator()==1)
							strcpy(sr4,"YES");
							else
							strcpy(sr4,"NO");
						
							printf("\n%-10d %-10s %.2f %-10s %10d %-10s %10c %-10s %-10s %.2f",i1,fo1.pname,fo1.psize,sr1,fo1.rooms,sr3,toupper(fo1.purchasetype),sr4,sr2,fo1.baserate);//co1.pname<<co1.psize<<sr1<<co1.get_shops()<<toupper(co1.purchasetype)<<co1.get_zonename()<<co1.baserate;
						}
						f2ptr.read((char*)&fo1,sizeof(flat));
					}
					cout<<"\nEnter desired property number: ";
					cin>>i1;
					while(i1<1 || i1>count)
					{
						cout<<"\nIncorrect value. Enter valid property number: ";
						cin>>i1;
					}
					i1-=1;
					comarr[i1].displaydetails();
					cout<<"\nAll property details now displayed. Press any key to continue...";
					getchar();
					getchar();
					}
			}
		}
		
		f1ptr.close();
		f2ptr.close();
		f3ptr.close();
	}
	
	
	
//class guest privately inherited for security purposes and since no signup is needed
//does not have write privileges to system files
//can only be used to display relevant data to user
class guest: private user{
	vector<house>hwish;//vectors used for dynamic updation of wishlists
	vector<flat>fwish;
	vector<commercial>cwish;
	int guestid;
	public:
	guest()
	{
	}
	~guest()
	{
		cout<<"\n******************************************PLEASE VISIT US AGAIN, OR RECCOMMEND US TO A FRIEND!******************************************\n";
	}
	void Welcome()
	{
		cout<<"\n\t\t\t\t************GUEST PORTAL************\n\n\n";
	}
	
	void Menu2()
	{
		srand(time(0));
		guestid=rand();
		cout<<"\n\nGuest ID for this session: "<<guestid<<"\nPress any key to proceed...";
		getchar();
		getchar();
		Menu1();
	}
	
	void Menu1()
	{
		int c;
		Welcome();
		while(1)
		{
			system("cls");
			cout<<"\n\n\t\t\n1. View Available Properties\n2. View Agent Information\n3.Update Wishlist\n4. View Wishlist\n5. Logout\n\nEnter your choice: ";
			cin>>c;
			while(c<1 || c>5)
			{
				cout<<"\nInvalid input. Enter valid choice: ";
				cin>>c;
			}
			if(c==1)
			{
				cout<<"\n\n\nNOW ENTERING PROPERTY PORTAL\n\n\n";
				ViewProperties();//call to global function
			}
			else if(c==2)
			{
				ViewAgentInfo();
			}
			else if(c==3)
			{
				updateList();//update wishlists
			}
			else if(c==4)
			{
				viewList();//view wishlists
			}
			else if(c==5)
			{
				Logout();
				break;
			}
		}
	}
	
	int viewList()
	{
		
		int ch,ch2;
		char str1[50];
		cout<<"\n\nWhich WishList would you like to view?\n1. Commercial\n2. House\n3. Flat\n\nEnter your choice: ";
		cin>>ch;
		while(ch<1 || ch>3)
		{
			cout<<"\nEnter valid choice: ";
			cin>>ch;
		}
		if(ch==1)
		{
			if(cwish.size()==0)
			{
					cout<<"\nYour Commercial Wishlist is currently empty. Press any key to continue.\n\n";
					getchar();
					getchar();
					return 1;
			}
			
			printf("\nWishlisted Commercial Properties: \n\n");
			printf("\n| %10s | %10s | %10s | %10s | %10s | %10s |\n","S. No.","Name","Size (Sq. Guz)","Property ID","Base Rate (Rs.)","Available");
			for(int i=0;i<cwish.size();i++)
			{
				if(cwish[i].getAvailable()==1)
					strcpy(str1,"YES");
					else
					strcpy(str1,"NO");
					printf("\n%10d %10s %10.2f %10d %10.2f %10s\n",i+1,cwish[i].get_pname(),cwish[i].get_psize(),cwish[i].get_propertyid(),cwish[i].get_Baserate(),str1);
			}
			cout<<"\nEnter desired serial no. for property: ";
			cin>>ch2;
			while(ch2<1 || ch2>cwish.size())
			{
				cout<<"\nINvalid entry. Enter valid value within range: ";
				cin>>ch2;
			}
			ch2-=1;
			cout<<"\nNow showing property details:\n\n ";
			cwish[ch2].displaydetails();
		}
		else if(ch==2)
		{
			if(hwish.size()==0)
			{
					cout<<"\nYour House Wishlist is currently empty. Press any key to continue.\n\n";
					getchar();
					getchar();
					return 1;
			}
			printf("\nWishlisted Residential House Properties: \n\n");
			printf("\n| %10s | %10s | %10s | %10s | %10s | %10s |\n","S. No.","Name","Size (Sq. Guz)","Property ID","Base Rate (Rs.)","Available");
			for(int i=0;i<hwish.size();i++)
			{
				if(hwish[i].getAvailable()==1)
					strcpy(str1,"YES");
				else
					strcpy(str1,"NO");
					printf("\n%10d %10s %10.2f %10d %10.2f %10s\n",i+1,hwish[i].get_pname(),hwish[i].get_psize(),hwish[i].get_propertyid(),hwish[i].get_Baserate(),str1);
			}
			cout<<"\nEnter desired serial no. for property: ";
			cin>>ch2;
			while(ch2<1 || ch2>hwish.size())
			{
				cout<<"\nINvalid entry. Enter valid value within range: ";
				cin>>ch2;
			}
			ch2-=1;
			cout<<"\nNow showing property details:\n\n ";
			hwish[ch2].displaydetails();
		}
		else if(ch==3)
		{
			if(fwish.size()==0)
			{
					cout<<"\nYour Flat Wishlist is currently empty. Press any key to continue.\n\n";
					getchar();
					getchar();
					return 1;
			}
			
			printf("\nWishlisted Flat Properties: \n\n");
			printf("\n| %10s | %10s | %10s | %10s | %10s | %10s |\n","S. No.","Name","Size (Sq. Guz)","Property ID","Base Rate (Rs.)","Available");
			for(int i=0;i<fwish.size();i++)
			{
				if(fwish[i].getAvailable()==1)
					strcpy(str1,"YES");
					else
					strcpy(str1,"NO");
					printf("\n%10d %10s %10.2f %10d %10.2f %10s\n",i+1,fwish[i].get_pname(),fwish[i].get_psize(),fwish[i].get_propertyid(),fwish[i].get_Baserate(),str1);
			}
			cout<<"\nEnter desired serial no. for property: ";
			cin>>ch2;
			while(ch2<1 || ch2>fwish.size())
			{
				cout<<"\nInvalid entry. Enter valid value within range: ";
				cin>>ch2;
			}
			ch2-=1;
			cout<<"\nNow showing property details:\n\n ";
			fwish[ch2].displaydetails();
		}
		cout<<"\n\nWishlist displayed! Press any key to continue: ";
		getchar();
		getchar();
	}
	
	int updateList()
	{
		int choice,ch2;
		int count=0;
		int index=0;
		char str1[50],str2[50],str3[50],str4[50];
		cout<<"\n\nWhich type of property would you like to see?\n1. Commercial\n2. Residential\n\nEnter your choice: ";
		cin>>choice;
		while(choice<1 || choice>2)
		{
			cout<<"\ninvalid entry. Enter valid choice: ";
			cin>>choice;
		}
		if(choice==1)
		{
			
			fstream comptr;
			string comn="Commercial.dat";
			comptr.open(comn.c_str(),ios::binary|ios::in|ios::out);
			comptr.seekg(0,ios::end);
			if(comptr.tellg()==0)
			{
				cout<<"\nNo commercial properties to display.\n\nPress any key to continue: ";
				getchar();
				getchar();
				return 1;
			}
			if(!comptr)
			{
				cout<<"\nError opening file\n";
				exit(1);
			}
			commercial cmr1;
			comptr.seekg(0,ios::beg);
			comptr.read((char*)&cmr1,sizeof(commercial));
		
			while(!comptr.eof())
			{
				if(cmr1.getAvailable()==1)
				count++;
				comptr.read((char*)&cmr1,sizeof(commercial));
			}
			if(count==0)
			{
				cout<<"\nNo available commercial properties to display.\n\nPress any key to continue: ";
				comptr.close();
				getchar();
				getchar();
				return 1;
			}
			
			commercial comarr[count];
			comptr.clear();
			comptr.seekg(0,ios::beg);
			printf("\nCommercial Properties: \n\n");
			printf("\n| %10s | %10s | %10s | %10s | %10s | %10s |\n","S. No.","Name","Size (Sq. Guz)","Property ID","Base Rate (Rs.)","Available");
			comptr.read((char*)&cmr1,sizeof(commercial));
				while(!comptr.eof())
				{
					if(cmr1.getAvailable()==1)
					{
					comarr[index]=cmr1;
					index++;
					if(cmr1.getAvailable()==1)
					strcpy(str1,"YES");
					else
					strcpy(str1,"NO");
					printf("\n%10d %10s %10.2f %10d %10.2f %10s\n",index,cmr1.get_pname(),cmr1.get_psize(),cmr1.get_propertyid(),cmr1.get_Baserate(),str1);
					}
					comptr.read((char*)&cmr1,sizeof(commercial));
				}
				cout<<"\nEnter a property number to be viewed: ";
				cin>>ch2;
				while(ch2<1 || ch2>count)
				{
					cout<<"\nInvalid input. Please enter valid number: ";
					cin>>ch2;
				}
				ch2-=1;
				cout<<"\nNow showing property details\n";
				comarr[ch2].displaydetails();
				cwish.push_back(comarr[ch2]);
				cout<<"\n\nProperty added to your wishlist!\n";
		}
		else
		{
			int hr;
			cout<<"\n\n1. Houses\n2. Flats\n\nEnter your choice: ";
			cin>>hr;
			while(hr<1 || hr>2)
			{
				cout<<"\nInvalid entry. Enter valid choice: ";
				cin>>hr;
			}
			if(hr==1)
			{
				string hname="House.dat";
				fstream hptr;
				hptr.open(hname.c_str(),ios::binary|ios::in|ios::out);
				if(!hptr)
				{
					cout<<"\nError opening file.\n";
					exit(1);	
				}	
				house h1;
				hptr.read((char*)&h1,sizeof(house));
				while(!hptr.eof())
				{
					if(h1.getAvailable()==1)
					{
						count++;
					}
					hptr.read((char*)&h1,sizeof(house));
				}
				if(count==0)
				{
					cout<<"\nNo houses to display.\n\nPress any key to continue: ";
					hptr.close();
					getchar();
					getchar();
				}
				else
				{
				hptr.clear();
				hptr.seekg(0,ios::beg);
				house harr[count];
				printf("\nResidential Properties: \n\n");
				printf("\n| %10s | %10s | %10s | %10s | %10s | %10s |\n","S. No.","Name","Size (Sq. Guz)","Property ID","Base Rate (Rs.)","Available");
				hptr.read((char*)&h1,sizeof(house));
				while(!hptr.eof())
				{
					if(h1.getAvailable()==1)
					{
					harr[index]=h1;
					index++;
					if(h1.getAvailable()==1)
					strcpy(str1,"YES");
					else
					strcpy(str1,"NO");
					printf("\n%10d %10s %10.2f %10d %10.2f %10s\n",index,h1.get_pname(),h1.get_psize(),h1.get_propertyid(),h1.get_Baserate(),str1);
					}
					hptr.read((char*)&h1,sizeof(house));
				}
				cout<<"\nEnter a property number to be viewed: ";
				cin>>ch2;
				while(ch2<1 || ch2>count)
				{
					cout<<"\nInvalid input. Please enter valid number: ";
					cin>>ch2;
				}
				ch2-=1;
				cout<<"\nNow showing property details\n";
				harr[ch2].displaydetails();
				//cout<<"\n\nSeller details: \nAgent Information: \nAgent Name: "<<harr[ch2].seller_name<<"\nAgent ID: AG1-"<<harr[ch2].ownerid<<endl;
				hwish.push_back(harr[ch2]);
				cout<<"\n\nProperty added to your wishlist!\n";
				cout<<"\nDetails displayed. Press any key to continue.";
				getchar();
				getchar();
				hptr.close();
				}
			}
			else
			{
				string hname="Flats.dat";
				fstream fptr;
				fptr.open(hname.c_str(),ios::binary|ios::in|ios::out);
				if(!fptr)
				{
					cout<<"\nError opening file.\n";
					exit(1);	
				}	
				flat f1;
				fptr.read((char*)&f1,sizeof(flat));
				while(!fptr.eof())
				{
					if(f1.getAvailable()==1)
					{
						count++;
					}
				fptr.read((char*)&f1,sizeof(flat));
				}
				if(count==0)
				{
					cout<<"\nNo flats to display.\n\nPress any key to continue: ";
					fptr.close();
					getchar();
					getchar();
				}
				else
				{
				fptr.clear();
				fptr.seekg(0,ios::beg);
				flat farr[count];
				printf("\nResidential Properties: \n\n");
				printf("\n| %10s | %10s | %10s | %10s | %10s | %10s |\n","S. No.","Name","Size (Sq. Guz)","Property ID","Base Rate (Rs.)","Available");
				fptr.read((char*)&f1,sizeof(flat));
				while(!fptr.eof())
				{
					if(f1.getAvailable()==1)
					{
					farr[index]=f1;
					index++;
					if(f1.getAvailable()==1)
					strcpy(str1,"YES");
					else
					strcpy(str1,"NO");
					printf("\n%10d %10s %10.2f %10d %10.2f %10s\n",index,f1.get_pname(),f1.get_psize(),f1.get_propertyid(),f1.get_Baserate(),str1);
					}
					fptr.read((char*)&f1,sizeof(flat));
				}
				cout<<"\nEnter a property number to be viewed: ";
				cin>>ch2;
				while(ch2<1 || ch2>count)
				{
					cout<<"\nInvalid input. Please enter valid number: ";
					cin>>ch2;
				}
				ch2-=1;
				cout<<"\nNow showing property details\n";
				farr[ch2].displaydetails();
				//cout<<"\n\nSeller details: \nAgent Information: \nAgent Name: "<<harr[ch2].seller_name<<"\nAgent ID: AG1-"<<harr[ch2].ownerid<<endl;
				fwish.push_back(farr[ch2]);
				cout<<"\n\nProperty added to your wishlist!\n";
				cout<<"\nDetails displayed. Press any key to continue.";
				getchar();
				getchar();
				fptr.close();
				}	
			}
		}
		cout<<"\nWishlist updated!\n\nPress any key to continue...";
		getchar();
		getchar();
	
	}
	
	int ViewAgentInfo()
	{
		fstream agentptr;
		agent a1;
		int acho;
		string afilename="AgentInfo.dat";
		int index=0;
		int count=0;
		agentptr.open(afilename.c_str(),ios::in|ios::out|ios::binary);
		if(!agentptr)
		{
			cout<<"\nError opening file\n";
			exit(1);
		}
		agentptr.read((char*)&a1,sizeof(agent));
		while(!agentptr.eof())
		{
			count++;
			agentptr.read((char*)&a1,sizeof(agent));
		}
		
		if(count==0)
		{
			cout<<"\nNo available agents to be displayed. Please try again later\n.";
			getchar();
			getchar();
			agentptr.close();
			return 1;
		}
		
		agent agearr[count];
		agentptr.clear();
		agentptr.seekg(0,ios::beg);
		agentptr.read((char*)&a1,sizeof(agent));
		printf("\nAgent Information:\n\n| %-10s | %-10s | %-10s |","Serial No.","Agent Name","Agent ID");
		while(!agentptr.eof())
		{
			agearr[index]=a1;
			index++;
			printf("\n\n%-10d %-10s AG - %-10d",index,a1.get_fullname(),a1.get_agentid());
			agentptr.read((char*)&a1,sizeof(agent));
			Sleep(200);
		}
		agentptr.clear();
		cout<<"\nEnter Serial No. of desired agent: ";
		cin>>acho;
		while(acho<1 || acho>count)
		{
			cout<<"\nInvalid entry. Enter valid number: ";
			cin>>acho;
		}
		acho-=1;
		cout<<"\n\n\nNow showing agent details: \n";
		cout<<"\nAgent Name: "<<agearr[acho].get_fullname()<<"\nAgent ID: "<<agearr[acho].get_agentid()<<"\nCompany Name: "<<agearr[acho].get_companyname()<<"\n\nAgent Description: \n"<<agearr[acho].get_description()<<"\nCommission Rate: "<<agearr[acho].get_crate()<<"%\nTotal Sales: "<<agearr[acho].get_totalsales()<<endl;
		cout<<"\n\nYou can contact Mr./Mrs. "<<agearr[acho].get_fullname()<<" at: \nEmail: "<<agearr[acho].get_useremail()<<"\nContact Number: "<<agearr[acho].get_contactno()<<"\n\n\n";
		cout<<"\n\n\nAgent information displayed. Press any key to continue.";
		getchar();
		getchar();
		agentptr.close();
	}
	
	void Logout()
	{
	time_t now = time(0);
   	char* date_time = ctime(&now);
   	Sleep(300);
	cout <<"\n\nNow logging out Guest "<<guestid;
    Sleep(200);
	cout<<"\n\nTime: "<< date_time << endl;
	Sleep(300);
	cout<<"\n\n\nTHANK YOU FOR USING OUR SYSTEM\n\n";
	Sleep(150);
	}
	
	
};

//independent class admin to view and manage all system files and accounts
class admin{
	public:
	admin()
	{	
	}
	~admin()
	{
	}
	void viewproperties();
	int Menu1()
	{
		int pin,attempts=3;// PIN = 4537
		cout<<"\nPlease enter authorization PIN before proceeding: ";
		cin>>pin;
		cout<<"\n";
		while(pin!=4537)
		{
			--attempts;
			if(attempts==0)
			{
				cout<<"\nUnable to authenticate administrator privileges. Now exiting...";
				Sleep(300);
				admin_logout();
				return 1;
			}
			cout<<"\nIncorrect PIN! Please try again (Attempts left: "<<attempts<<"): ";
			cin>>pin;	
		}
		int adch;
		while(1)
		{
			system("cls");
			cout<<"\n1. View Customer Accounts\n2. View Agent Accounts\n3. View Properties\n4. Logout\n\nEnter your choice: ";
			cin>>adch;
			while(adch!=1 && adch!=2 && adch!=3 && adch!=4 )
			{
				cout<<"\nInvalid input. Enter valid choice: ";
				cin>>adch;	
			}
			switch(adch)
			{
				case 1:
				Sleep(500);
				customer_accounts();
				break;
				
				case 2:
				Sleep(500);
				agent_accounts();
				break;
			
				case 3:
				Sleep(500);
				properties();
				break;
				
				default:
				Sleep(500); 
				admin_logout();
				break;	
			}
			
			if(adch==4)
			break;		 
		}
		
	}
	
	void admin_logout()
	{
		time_t now = time(0);
   char* date_time = ctime(&now);
   cout <<"\n\nNow logging out ADMIN\n\nTime of exit: "<< date_time << endl;
	cout<<"\n\n\n";
	Sleep(400);
	}
	
	void properties()
	{
		string cmpname;
		char str[50];
		int ch1,ch2,index,count;
		index=0;
		count=0;
		cout<<"\n******************************PROPERTIES******************************\n\n";
		cout<<"\n1. Commercial\n2. Residential\n\nEnter your choice: ";
		cin>>ch1;
		while(ch1<1 || ch1>2)
		{
			cout<<"\nInvalid entry. Enter your choice: ";
			cin>>ch1;
		}
		if(ch1==1)
		{
			count=0;
			commercial cmp1;
			fstream cmptr;
			char str[50];
			cmpname="Commercial.dat";
			cmptr.open(cmpname.c_str(),ios::in|ios::out|ios::binary);
			if(!cmptr)
			{
				cout<<"\nError opening file\n";
				exit(1);
			}
			cmptr.read((char*)&cmp1,sizeof(commercial));
			while(!cmptr.eof())
			{
				count++;
				cmptr.read((char*)&cmp1,sizeof(commercial));
			}
			cmptr.clear();
			cmptr.seekg(0,ios::beg);
			if(count==0)
			{
				cout<<"\nNo available commercial properties to display.\n";
				cmptr.close();
			}
			else
			{
				commercial comarr[count];
				printf("\nCommercial Properties: \n\n");
				printf("\n| %10s | %10s | %10s | %10s | %10s | %10s |\n","S. No.","Name","Size (Sq. Guz)","Property ID","Base Rate (Rs.)","Available");
				cmptr.read((char*)&cmp1,sizeof(commercial));
				while(!cmptr.eof())
				{
					comarr[index]=cmp1;
					index++;
					if(cmp1.available==1)
					strcpy(str,"YES");
					else
					strcpy(str,"NO");
					printf("\n%10d %10s %10.2f %10d %10.2f %10s\n",index,cmp1.pname,cmp1.psize,cmp1.propertyid,cmp1.baserate,str);
					cmptr.read((char*)&cmp1,sizeof(commercial));
				}
				cout<<"\nEnter a property number to be viewed: ";
				cin>>ch2;
				while(ch2<1 || ch2>count)
				{
					cout<<"\nInvalid input. Please enter valid number: ";
					cin>>ch2;
				}
				ch2-=1;
				cout<<"\nNow showing property details\n";
				cout<<comarr[ch2];
				cout<<"\n\nSeller details: \nAgent Information: \nAgent Name: "<<comarr[ch2].seller_name<<"\nAgent ID: AG1-"<<comarr[ch2].sellerid<<endl;
				cout<<"\nDetails displayed. Press any key to continue.";
				getchar();
				getchar();
				cmptr.close();
			}
			
		}
		else
		{
			int hf;
			cout<<"\n**********RESIDENTIAL**********\n\n1. Houses\n2. Flats\n\nEnter your choice: ";
			cin>>hf;
			while(hf<1 || hf>2)
			{
				cout<<"\nInvalid input. Enter valid choice: ";
				cin>>hf;
			}
			if(hf==1)
			{
				house h1;
	
				index=0;
				count=0;
				fstream hptr;
				cmpname="House.dat";
				hptr.open(cmpname.c_str(),ios::in|ios::out|ios::binary);
				if(!hptr)
				{
					cout<<"\nError opening file\n";
					exit(1);
				}
				hptr.read((char*)&h1,sizeof(house));
				while(!hptr.eof())
				{
					count++;
					hptr.read((char*)&h1,sizeof(house));
				}
				hptr.clear();
				hptr.seekg(0,ios::beg);
				if(count==0)
				{
					cout<<"\nNo available residential properties to display.\n";
					hptr.close();
				}
				else
				{
				house harr[count];
				printf("\nResidential Properties: \n\n");
				printf("\n| %10s | %10s | %10s | %10s | %10s | %10s |\n","S. No.","Name","Size (Sq. Guz)","Property ID","Base Rate (Rs.)","Available");
				hptr.read((char*)&h1,sizeof(house));
				while(!hptr.eof())
				{
					harr[index]=h1;
					index++;
					if(h1.available==1)
					strcpy(str,"YES");
					else
					strcpy(str,"NO");
					printf("\n%10d %10s %10.2f %10d %10.2f %10s\n",index,h1.pname,h1.psize,h1.propertyid,h1.baserate,str);
					hptr.read((char*)&h1,sizeof(house));
				}
				cout<<"\nEnter a property number to be viewed: ";
				cin>>ch2;
				while(ch2<1 || ch2>count)
				{
					cout<<"\nInvalid input. Please enter valid number: ";
					cin>>ch2;
				}
				ch2-=1;
				cout<<"\nNow showing property details\n";
				//harr[ch2].displaydetails();
				cout<<harr[ch2];
				cout<<"\n\nSeller details: \nAgent Information: \nAgent Name: "<<harr[ch2].seller_name<<"\nAgent ID: AG1-"<<harr[ch2].sellerid<<endl;
				cout<<"\nDetails displayed. Press any key to continue.";
				getchar();
				getchar();
				hptr.close();
				}		
			}
			else if(hf==2)
			{
				count=0;
				flat f1;
				fstream fptr;
				cmpname="Flats.dat";
				fptr.open(cmpname.c_str(),ios::in|ios::out|ios::binary);
				if(!fptr)
				{
					cout<<"\nError opening file\n";
					exit(1);
				}
				fptr.read((char*)&f1,sizeof(flat));
				while(!fptr.eof())
				{
					count++;
					fptr.read((char*)&f1,sizeof(flat));
				}
				fptr.clear();
				fptr.seekg(0,ios::beg);
				if(count==0)
				{
					cout<<"\nNo available residential properties to display.\n";
					fptr.close();
				}
				else
				{
					flat farr[count];
					printf("\nFlats: \n\n");
					printf("\n| %10s | %10s | %10s | %10s | %10s | %10s |\n","S. No.","Name","Size (Sq. Guz)","Property ID","Base Rate (Rs.)","Available");
					fptr.read((char*)&f1,sizeof(flat));
					while(!fptr.eof())
					{
					farr[index]=f1;
					index++;
					if(f1.available==1)
					strcpy(str,"YES");
					else
					strcpy(str,"NO");
					printf("\n%10d %10s %10.2f %10d %10.2f %10s\n",index,f1.pname,f1.psize,f1.propertyid,f1.baserate,str);
					fptr.read((char*)&f1,sizeof(flat));
					}
					cout<<"\nEnter a property number to be viewed: ";
					cin>>ch2;
					while(ch2<1 || ch2>count)
					{
					cout<<"\nInvalid input. Please enter valid number: ";
					cin>>ch2;
					}
					ch2-=1;
					cout<<"\nNow showing property details\n";
					//farr[ch2].displaydetails();
					cout<<farr[ch2];
					cout<<"\n\nSeller details: \nAgent Information: \nAgent Name: "<<farr[ch2].seller_name<<"\nAgent ID: AG1-"<<farr[ch2].sellerid<<endl;
					cout<<"\nDetails displayed. Press any key to continue.";
					getchar();
					getchar();
					fptr.close();
				}		
			}
		}
	}
	
	void customer_accounts()
	{
		fstream custptr;
		char pstr[50];
		strcpy(pstr,"Disabled");
		customer c1;
		string cfilename="CustomerInfo.dat";
		custptr.open(cfilename.c_str(),ios::in | ios::out | ios::binary);
		if(!custptr)
		{
			cout<<"\nError opening file\n";
			exit(1);
		}
		custptr.read((char*)&c1,sizeof(customer));
		printf("\nCustomer Information:\n\n| %10s %10s %10s %10s %10s %10s %10s %10s %10s %10s %10s | \n","Username","Password","Name","Email","Contact No.","ID","Total Properties","Budget","Account Total","Buy Total","Rent Total");
		while(!custptr.eof())
		{
			if(c1.get_budget()==-1)
			{
				printf("\n\n%10s %10s %10s %10s %10s %10d %10d %10s %10.2f %10.2f %10.2f",c1.uname,c1.upass,c1.fullname,c1.useremail,c1.contactno,c1.custid,c1.get_tprops(),pstr,c1.get_acctotal(),c1.get_buytotal(),c1.get_renttotal());
			}
			else
			printf("\n\n%10s %10s %10s %10s %10s %10d %10d %10.2f %10.2f %10.2f %10.2f",c1.uname,c1.upass,c1.fullname,c1.useremail,c1.contactno,c1.custid,c1.get_tprops(),c1.get_budget(),c1.get_acctotal(),c1.get_buytotal(),c1.get_renttotal());
			custptr.read((char*)&c1,sizeof(customer));
			Sleep(400);
		}
		custptr.clear();
		cout<<"\n\n\nAll customer accounts displayed. Press any key to continue.";
		getchar();
		getchar();
		custptr.close();
	}
	void agent_accounts()
	{
		fstream agentptr;
		agent a1;
		string afilename="AgentInfo.dat";
		agentptr.open(afilename.c_str(),ios::in|ios::out|ios::binary);
		if(!agentptr)
		{
			cout<<"\nError opening file\n";
			exit(1);
		}
		agentptr.read((char*)&a1,sizeof(agent));
		printf("\nAgent Information:\n\n| %-10s %10s %15s %25s %18s %15s %15s %10s %15s %15s |\n","Username","Password","Name","Email","Contact No.","ID","Total Sold","Income","Commission Rate(%)","Rent Collected");
		while(!agentptr.eof())
		{
			printf("\n%-10s %10s %20s %25s %15s %15d %10d %15.2f %15.2f %15.2f",a1.uname,a1.upass,a1.fullname,a1.useremail,a1.contactno,a1.agentid,a1.totalsales,a1.income,a1.get_crate(),a1.rentcollected);
			agentptr.read((char*)&a1,sizeof(agent));
			Sleep(400);
		}
		agentptr.clear();
		cout<<"\n\n\nAll agent accounts displayed. Press any key to continue.";
		getchar();
		getchar();
		agentptr.close();
	}
};
//global function to validate user passwords for registration or password updation
int checkpass(char *str)
{
	int c1=0,c2=0,c3=0;
	for(int i=0;str[i]!='\0';i++)
	{
		c1++;
	}
	if(c1>50 || c1<8)
	return 0;
	for(int i=0;str[i]!='\0';i++)
	{
		if(str[i]>='A' && str[i]<='Z')
		c2++;
	}
	if(c2==0)
	return 0;
	for(int i=0;str[i]!='\0';i++)
	{
		if(str[i]==' ')
		c3++;
	}
	if(c3>0)
	return 0;
	
	return 1;
}

//Driver program
int main()
{
	int mchoice;
	cout<<"***********************************REAL ESTATE AGENCY***********************************\n\n\n";
	cout<<"How would you like to proceed?\n\n1. User\n2. Admin\nEnter your choice: ";
	cin>>mchoice;
	//calls the menu member function of respective class
	if(mchoice==1)
	{
		int uch;
		cout<<"\n\tUSER\n1. Customer\n2. Agent\n3. Guest\n\nEnter your choice: ";
		cin>>uch;
		while(uch<1 || uch>3)
		{
			cout<<"\nInvalid entry. Enter valid choice: ";
			cin>>uch;
		}
		if(uch==1)
		{
			customer cmr;
			cmr.Menu1();
		}
		else if(uch==2)
		{
			agent agr;
			agr.Menu1();
		}
		else if(uch==3)
		{
			guest gst;
			gst.Menu2();
		}
	}
	else
	{
		admin adm;
		adm.Menu1();
	}
}
