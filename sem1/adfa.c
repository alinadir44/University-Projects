#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<Windows.h>
#include<time.h>
#include<ctype.h>
/* Admin: 1.add route(needed for adding bookings) 2. add flight(for bookings and tickets) 3. manage accounts(display info of customers) 4. logout
 5.Update pricing(for seat class(base price same for all routes) AND routes(tax and will be non zero)) 6.View pricing 7. View customer feedback*/

typedef struct ratings{
	int fives;
	int fours;
	int threes;
	int twos;
	int ones;
}ratings;

typedef struct rankings{
	char fcode[30];
	int pts;
	ratings review;
}rankings;
 
typedef struct Feedback{
	char feedstr[150];
	int booknum;
}feedbacks;
 
typedef struct Route{
	char origin[20];
	char destination[20];
	char routecode[20];
	int routeprice;	
}routes;
typedef struct Flight{
	char flightcode[7];
	int tseats;
	int full;
	int seats[4][50];
	char froute[20];	
}flights;

typedef struct Ticket{
	int bookno;
	int seatno;
	int rowno;
	char flightno[7];
	char fclass;
	char meal;	
}tickets;

typedef struct Booking{
	int cnum;
	int bookno;
	int bookcost;
	char origin[20];
	char destination[20];	
}bookings;

typedef struct Customer{
 int cnum;
 char uname[30];
 char upass[30];
 char fname[40];
 char lname[40];
 int cardnum;
 int costdue;
}customers;


int cno=1110;
int ulogin(FILE **ptr,FILE **fp,char* fname,char* cfname,char* str,int* cval);
void currenttime();
int getpin();
void displayadminmenu();
void addroute(FILE **routeptr);
void addflight(FILE **flightptr,FILE **routeptr,FILE **rankptr);
int checkroutecode(char* code);
void viewrouteprice(FILE **routeptr);
void viewticketprice(FILE **ticketptr);
void changeticketprice(FILE **ticketptr);
void displayusermenu();
void viewaccountinfo(FILE **ptr,int cnumber);
void addbookings(FILE **ptr,FILE **ticketptr,FILE **routeptr,FILE **flightptr,FILE **bookptr,FILE **tickptr,int customernumber,FILE **rankptr);
void checkflightscode(char* fcode);
void viewbookinginfo(FILE **bookptr,FILE **tickptr,int custno);
void displaycustinfo(FILE **ptr);
void viewadminflight(FILE **flightptr);
void addfeedbacks(FILE **feedptr,FILE **bookptr,int custno);
void adminrank(FILE **flightptr, FILE **rankptr);
void viewranks(FILE **rankptr);
void viewamdinrnaks(FILE **rankptr);

int main()
{
	 int cvalue=0;
	 const int pin=4897;
	 FILE *rankptr;
	 FILE *ticketptr;
	 FILE *tickptr;
	 FILE *bookptr;
	 FILE *fp,*ptr;
	 char cn[40];
	 FILE *routeptr;
	 FILE *flightptr;
	 FILE *feedptr;
	 int val,uchoice=2;
	 int adminchoice,usechoice;
	 char userresult;
	 printf("\t\t\t\t****************CRM AGENCY****************\n\n\n\n");
	 Sleep(300);
	 printf("\t\t\t\t****************LOGIN PORTAL****************\n\n\n");
	 Sleep(300);
	 
	 
	 printf("\t\t\t\tPlease Enter:\n\n\n\t\t\t\t1 - To proceed as USER\n\n\t\t\t\t2 - To proceed as ADMINISTRATOR\n\t\t\t\t0 to exit\n\n\n\t\t\t\tPlease Enter Your Choice... ");
	 scanf(" %c",&userresult);
	 
	 
	 while((userresult!='1') && (userresult!='2') && (userresult!='0'))
	 {
	 	printf("\n\n\t\t\t\tPlease enter valid choice!\n\n");
	 	printf("\t\t\t\tPlease Enter:\n\t1 - To proceed as USER\n\t2 - To proceed as ADMINISTRATOR\n\n\t0 - to exit\n\tPlease Enter Your Choice... ");
	 	scanf(" %c",&userresult);
	 }
	 if (userresult=='1')
	 {
	 	printf("\n\n\n\t\t\t\tREDIRECTING TO USER PORTAL\n\n\n");
	 	sleep(1);
	 	printf("\n\n\n\t\t\t\tPLEASE WAIT...\n\n");
	 	sleep(2);
		printf("\n\n\n\n\t\t\t***********************  W E L C O M E   T O   C U S T O M E R   L O G I N  *************************\n\n\n");
	 	Sleep(800);
		val=ulogin(&ptr,&fp,"UserInfo.txt","CustomerInfo.dat",cn,&cvalue);
	 	
		/*if (val==1)
	 	{
	 		printf("\n\n\n\tREDIRECTING TO USER\n\n\n");
	 		
		}
		else
		{*/
			
			while((val!=1 && val!=2) || uchoice!=2)
			{
				printf("\n\n\n\t\t\tFailed To Login\n\tEnter:\n\t1. Retry\n\t2. Exit\n\t\t\t\tEnter you choice... ");
				scanf(" %d",&uchoice);
				if (uchoice==1)
				{
					val=ulogin(&ptr,&fp,"UserInfo.txt","CustomerInfo.dat",cn,&cvalue);
					if (val==1 || val==2)
					{
						uchoice=1;
						break;
					}
					
				}
				
			}
			if(val==1)
			{
				uchoice=1;
			}
			if (uchoice==2 || val==2)
			{
				
					printf("\n\n\n\t\t\t******************************** NOW  EXITING ********************************\n\n\n\n\n\n\n");
					sleep(1);
					return 0;
			}
			else
			{
					Sleep(500);
					printf("\n\n\n\t\t\tREDIRECTING TO USER PORTAL\n\n\n");
					Sleep(500);
					printf("\n\n\n\n\t\t\tWelcome back, %s\tTIME ACCESSED: ",cn);
					currenttime();
					printf("\n\n\t\t\tPRESS ANY KEY TO PROCEED....\n\n");
					getch();
					Sleep(400);
					//modules for user
					while(1)
					{
						system("cls");
						Sleep(400);
						displayusermenu();
						scanf("%d",&usechoice);
						switch(usechoice)
						{
							case 1: //Add booking
								addbookings(&ptr,&ticketptr,&routeptr,&flightptr,&bookptr,&tickptr,cvalue,&rankptr);
								break;
							case 2: //Access account info 
								viewaccountinfo(&ptr,cvalue);
								Sleep(400);
								break;
							case 3: //View latest ticket prices
								viewticketprice(&ticketptr);
								break;
							case 4: //View Route info
								viewrouteprice(&routeptr);
								break;
							case 5://View booking info
								viewbookinginfo(&bookptr,&tickptr,cvalue);
								Sleep(400);
								break;
							case 6://Add feedback
								addfeedbacks(&feedptr,&bookptr,cvalue);
								Sleep(400);
								break;	
							case 7://View updated rankings
								viewranks(&rankptr);
								Sleep(400);
								break;	
							case 8: //Logout
								Sleep(400);
								printf("\n\n\n\t\t\tNow Logging Out ... Customer: %d\n\n",cvalue);
								Sleep(400);
								break;
							default:
								printf("\n\nInvalid choice entered.\n\n");
								break;				
						}
						
						if (usechoice==8)
						{
							Sleep(400);				
							printf("\n\n\t\t\t\tDear  %s,  Thankyou For Choosing Us! FLY SAFE!\n\n",cn);
							return 0;
						}
						
					}
			}
		//}
	 }
	 else if(userresult=='2')
	 {
		if (getpin()==pin)
		{
			printf("\n\n\t**************** ACCESS GRANTED TO ADMINISTRATOR. YOU ARE LOGGED IN ****************\n\n");
			Sleep(800);
			while(1)
			{
				system("cls"); 
				//modules for admin
				Sleep(400);
				displayadminmenu();				
				scanf("%d",&adminchoice);
				switch (adminchoice)													
				{
				 	case 1: //Add a route
						  addroute(&routeptr);				 		
					 	  break;																				 
					case 2://Add a flight
						  addflight(&flightptr,&routeptr,&rankptr);
					 	  break;
					case 3://Check route prices
						viewrouteprice(&routeptr);
					 	  break;
					case 4://view flights
						viewadminflight(&flightptr);
					 	  break; 	  
					case 5://view each ticket types price
						viewticketprice(&ticketptr);
					 	  break;
					case 6://set ticket type price
						changeticketprice(&ticketptr);
					 	  break;
					case 7://Customer accounts
						displaycustinfo(&ptr);
					 	  break;
					case 8://Reset Rankings
						adminrank(&flightptr,&rankptr);
					 	  break;
					case 9://View Rankings(Unsorted)
						viewamdinrnaks(&rankptr);
					 	  break;
					case 10:
						printf("\n\n\t\t*********************** NOW LOGGING OUT *************************\n\n");
					 	  break;
					default:
						printf("\n\n\tInvalid choice entered\n\n");
					 	  break;	   	   	   	   	    	  
				}																					 
				if (adminchoice==10)
				{				
					printf("\n\n\tThankyou for choosing us.\n\n\tTime of Exit: ");
					Sleep(300);
					currenttime();
					return 0;
				}
			}
		}
		else
		{
			printf("\n\n\t\t\t\tInvalid pin entered.\n\n");
			return 0;
		}
	 }
	 else if(userresult=='0')
	 {
	 	printf("\n\n\n\t\t\t\t****************NOW EXITING...****************\n\n\n");
	 	Sleep(500);
	 }
	 
}//end of main

void viewamdinrnaks(FILE **rankptr)
{
	rankings avrank;
	*rankptr=fopen("Rankings.dat","rb+");
	if(*rankptr==NULL)
	{
		printf("\n\n\tError opening file\n\n");
		exit(1);
	}
	
	printf("\n\n\n\t ||Flight-Code|\t|5 stars|\t|4 stars|\t|3 stars|\t|2 stars|\t|1 star|\t|Points||\n\n");
	Sleep(250);
	while(fread(&avrank,sizeof(rankings),1,*rankptr)==1)
	{
		printf("%10s\t%10d\t%10d\t%10d\t%10d\t%10d\t%10d\n",avrank.fcode,avrank.review.fives,avrank.review.fours,avrank.review.threes,avrank.review.twos,avrank.review.ones,avrank.pts);
		Sleep(250);
	}
	printf("\n\n\tAll rankings now displayed!\n\tPress any key to continue...");
	getch();
	fclose(*rankptr);
}

void adminrank(FILE **flightptr, FILE **rankptr)
{
	flights userflight;
	rankings urank;
	int usechoice=0;
	*flightptr=fopen("FlightsInfo.dat","rb+");
	if(flightptr==NULL)
	{
		printf("\n\n\tError opening FlightsInfo.dat\n");
		exit(1);
	}
	else
	{
		printf("\n\n\tEnter:\n\n\t\t1. To Initialise/Reset Flight Rankings For All Flights\n\t\t2. Exit\n\n");
		scanf("%d",&usechoice);
		while(usechoice<1 || usechoice>2)
		{
			printf("\n\n\t**Invalid Entry!**\n\tEnter:\n\n\t\t1. To Initialise/Reset Flight Rankings For All Flights\n\t\t2. Exit\n\n");
			scanf("%d",&usechoice);
		}
		if(usechoice==1)
		{
			printf("\n\n\tALERT! All Flight Rankings and User Ratings(*) Will Now Be Erased/Reset!\n\n\tPress any key to continue");
			getch();
			*rankptr=fopen("Rankings.dat","wb+");
			while(fread(&userflight,sizeof(flights),1,*flightptr)==1)
			{
				strcpy(urank.fcode,userflight.flightcode);
				urank.pts=0;
				urank.review.fives=0;
				urank.review.fours=0;
				urank.review.threes=0;
				urank.review.twos=0;
				urank.review.ones=0;
				fwrite(&urank,sizeof(rankings),1,*rankptr);
			}
			printf("\n\t************All flight rankings cleared to default************\nPress any key to continue...");
			getch();
			fclose(*rankptr);
			fclose(*flightptr);
		}
		else
		{
			Sleep(300);
			printf("\n\n\tExiting...");
			Sleep(400);
			fclose(*flightptr);
		}
	}
}

void viewranks(FILE **rankptr)
{
	rankings vrank;
	rankings temp;
	flights vflight;
	int rcount=0;
	int i=0,j,k;
	*rankptr=fopen("Rankings.dat","rb+");
	if(*rankptr==NULL)
	{
		printf("\n\nError opening file\n\n");
		exit(1);
	}
	while(fread(&vrank,sizeof(rankings),1,*rankptr)==1)
	{
		rcount++;
	}
	rankings rankarr[rcount];
	rewind(*rankptr);
	while(fread(&vrank,sizeof(rankings),1,*rankptr)==1)
	{
		rankarr[i]=vrank;
		i++;
	}
	
	for(j=0;j<i;j++)
	{
		for(k=0;k<i;k++)
		{
			if(rankarr[k].pts<rankarr[k+1].pts)
			{
				temp=rankarr[k];
				rankarr[k]=rankarr[k+1];
				rankarr[k+1]=temp;
			}
		}
	}
	printf("\n\n\n\t ||Rank|\t|Flight-Code|\t|5 stars|\t|4 stars|\t|3 stars|\t|2 stars|\t|1 star|\t|Points||\n\n");
	for(j=0;j<i;j++)
	{
		Sleep(250);
		printf("%10d\t%10s\t%10d\t%10d\t%10d\t%10d\t%10d\t%10d\n",j+1,rankarr[j].fcode,rankarr[j].review.fives,rankarr[j].review.fours,rankarr[j].review.threes,rankarr[j].review.twos,rankarr[j].review.ones,rankarr[j].pts);
	}
	printf("\n\tPress any key to continue...");
	getch();
	fclose(*rankptr);
}

void addfeedbacks(FILE **feedptr,FILE **bookptr,int custno)
{
	int counter=0,sno=0,i=0;
	bookings userbooking,currentbooked;
	feedbacks userfeed;
	char chchoice='y';
	int uinput;
	int found=1;
	*bookptr=fopen("BookingInfo.dat","rb+");
	if(*bookptr==NULL)
	{
		printf("\n\nCould not open file\n\n");
		exit(1);
	}
	else
	{
		
		while(fread(&userbooking,sizeof(bookings),1,*bookptr)==1)
		{
			if(userbooking.cnum==custno)
			{
				counter++;				
			}
		}
		
		if(counter==0)
		{
			printf("\n\n\tNo bookings to show. Please make a booking first.\n\n");
			fclose(*bookptr);
			Sleep(400);
		}
		else if(counter>0)
		{
			bookings bookarr[counter];
			printf("\n\n\t\tCustomer Number: %d\n\n",custno);
			while(1)
			{
			system("cls");	
			rewind(*bookptr);
			printf("\n\n\t\tS.No\tBooking No.\tOrigin\tDestination\tBooking Cost\n");
			sno=0;
			while(fread(&userbooking,sizeof(bookings),1,*bookptr)==1)
			{
				if(userbooking.cnum==custno)
				{
					bookarr[i]=userbooking;
					i++;
					sno++;
					Sleep(200);
					printf("\n\n\t\t%-10d\t%10d\t%10s\t%10s\t%-10d PKR\n",sno,userbooking.bookno,userbooking.origin,userbooking.destination,userbooking.bookcost);
				}
			}
			printf("\n\n");
			Sleep(300);
			printf("\n\n\t\tEnter Serial Number: ");
			scanf(" %d",&uinput);
			while(uinput<1 || uinput>counter)
			{
				printf("\n\n\t\tIncorrect Number entered! Enter valid S.No : ");
				scanf(" %d",&uinput);
			}
			currentbooked=bookarr[uinput-1];
			*feedptr=fopen("Feedbacks.dat","ab+");
			if(*feedptr==NULL)
			{
				printf("\n\n\t\tCould not open file\n");
				fclose(*bookptr);
				exit(1);
			}
			else
			{
				fseek(*feedptr,0,SEEK_END);
				if (ftell(*feedptr)==0)
				{
					rewind(*feedptr);
					userfeed.booknum=currentbooked.bookno;
					printf("\n\n\t\tEnter any key to proceed further: ");
					getchar();
					Sleep(200);
					printf("\n\n\n\n\t\tPlease Enter Booking Feedback (Limit: 150 characters):\n\n\t\t");
					fgets(userfeed.feedstr,150,stdin);//
					fwrite(&userfeed,sizeof(feedbacks),1,*feedptr);
					Sleep(500);
					printf("\n\n\t\tFeedback for Booking No.: ");
					Sleep(400);
					printf("%d  ",currentbooked.bookno);
					Sleep(400);
					printf("stored successfully!");
					printf("\n\n\t\tEnter more feedback? Enter Yes to continue, or any other key to return: ");
					scanf(" %c",&chchoice);
					if( tolower(chchoice)!='y')
					{
						fclose(*feedptr);
						fclose(*bookptr);
						break;
						
					}
					else
					continue;
				}
				else
				{
					rewind(*feedptr);
					while(fread(&userfeed,sizeof(feedbacks),1,*feedptr)==1)
					{
						if (userfeed.booknum==currentbooked.bookno)
						{
							found=1;
							break;
						}
						else
						{
							found=0;
						}
					}
					if (found==0)
					{
						userfeed.booknum=currentbooked.bookno;
						printf("\n\n\t\tEnter any key to proceed further: ");
						getchar();
						Sleep(200);
						printf("\n\n\n\n\t\tPlease Enter Booking Feedback (Limit: 150 characters):\n\n\t\t");
						fgets(userfeed.feedstr,150,stdin);//
						fwrite(&userfeed,sizeof(feedbacks),1,*feedptr);
						Sleep(500);
						printf("\n\n\t\tFeedback for Booking No.: ");
						Sleep(300);
						printf("%d  ",currentbooked.bookno);
						Sleep(300);
						printf("stored successfully!");
						printf("\n\n\t\tEnter more feedback? Enter Yes to continue, or any other key to return: ");
						scanf(" %c",&chchoice);
						
						if( tolower(chchoice)!='y')
						{
							fclose(*feedptr);
							fclose(*bookptr);
							break;	
						}
						else
						continue;
						
					}
					else if (found==1)
					{
						Sleep(300);
						printf("\n\n\t\tFeedback found for Booking No: %d\n\n\t\t",userfeed.booknum);
						printf("%s",userfeed.feedstr);
						printf("\n\n\t\tALERT! Feedback for this booking has already been stored! Enter Yes to retry, or any other key to return: ");
						scanf(" %c",&chchoice);
						if( tolower(chchoice)!='y')
						{
							fclose(*feedptr);
							fclose(*bookptr);
							break;
						
						}
						else
						continue;
					}
					
				}
			}
	}
}
}
}

void viewadminflight(FILE **flightptr)
{
	flights vaf;
	char fcap[30];
	*flightptr=fopen("FlightsInfo.dat","rb+");
	if(*flightptr==NULL)
	{
		printf("\n\n\tError opening file\n\n");
		exit(1);
	}
	else
	{
		printf("\n\n\t    FlightCode\t   RouteCode\t    Capacity\t       Full\n");
		while(fread(&vaf,sizeof(flights),1,*flightptr)==1)
		{
			if(vaf.full==1)
			{
				strcpy(fcap,"Yes");
			}
			else
			{
				strcpy(fcap,"No");
			}
			Sleep(200);
			printf("\n\n\t%10s\t%10s\t%10d\t%10s",vaf.flightcode,vaf.froute,vaf.tseats,fcap);
		}
		fclose(*flightptr);
		Sleep(400);
		printf("\n\n\n\n\t\tAll flights available displayed\n\n\t\tPress any key to continue... ");
		getch();
	}
}

void displaycustinfo(FILE **ptr)
{
	customers custrec; 
	*ptr=fopen("CustomerInfo.dat","rb+");
	
	if(*ptr==NULL)
	{
		printf("\n\nCould not open file.\n\n");
		exit(1);
	}
	else
	{
		rewind(*ptr);
		printf("\n\t+============================================================================================+\n");
		printf("\t| Customer-Number |      Customer-Name      |Card-Number|  UserName   |  Password   |Cost-Due(PKR)|\n");
		printf("\t+===============================================================================================+\n");
		while(fread(&custrec,sizeof(customers),1,*ptr)==1)
		{
			printf("\t| %10d      | %-10s %-10s   |%10d | %10s  | %10s  | %10d |\n",custrec.cnum,custrec.fname,custrec.lname,custrec.cardnum,custrec.uname,custrec.upass,custrec.costdue);
			Sleep(200);
		}
		printf("\t+============================================================================================+\n\n");
		Sleep(400);
		printf("\n\n\tAll records available displayed\n\n");
		Sleep(300);
		printf("\n\n\tPress any key to continue...");
		getch();
		fclose(*ptr);
	}
}

void viewbookinginfo(FILE **bookptr,FILE **tickptr,int custno)
{
	int counter=0,sno=0,i=0;
	bookings userbooking,currentbook;
	tickets userticket;
	char cchoice='y';
	int uinput;
	char mealstr[30],cstr[30];
	*bookptr=fopen("BookingInfo.dat","rb+");
	if(*bookptr==NULL)
	{
		printf("\n\nCould not open file\n\n");
		exit(1);
	}
	else
	{
		
		while(fread(&userbooking,sizeof(bookings),1,*bookptr)==1)
		{
			if(userbooking.cnum==custno)
			{
				counter++;				
			}
		}
		
		if(counter==0)
		{
			printf("\n\n\tNo bookings to show. Please make a booking first.\n\n");
			fclose(*bookptr);
			Sleep(400);
			exit(1);
		}
		else if(counter>0)
		{
			bookings bookarr[counter];
			printf("\n\n\t\tCustomer Number: %d\n\n",custno);
			while(1)
			{
			system("cls");	
			rewind(*bookptr);
			printf("\n\n\t\tS.No\tBooking No.\tOrigin\tDestination\tBooking Cost\n");
			sno=0;
			i=0;
			while(fread(&userbooking,sizeof(bookings),1,*bookptr)==1)
			{
				if(userbooking.cnum==custno)
				{
					bookarr[i]=userbooking;
					i++;
					sno++;
					Sleep(200);
					printf("\n\n\t\t%-10d\t%10d\t%10s\t%10s\t%-10d PKR\n",sno,userbooking.bookno,userbooking.origin,userbooking.destination,userbooking.bookcost);
				}
			}
			printf("\n\n");
			Sleep(300);
			printf("\n\n\t\tEnter Serial Number: ");
			scanf(" %d",&uinput);
			while(uinput<1 || uinput>counter)
			{
				printf("\n\n\t\tIncorrect Number entered! Enter valid S.No : ");
				scanf(" %d",&uinput);
			}
			
			currentbook=bookarr[uinput-1];
			
			*tickptr=fopen("TicketingInformation.dat","rb+");
			if(*tickptr==NULL)
			{
				printf("\n\nError opening file\n\n");
				fclose(*bookptr);
				exit(1);	
			}
			else
			{
				rewind(*tickptr);
				printf("\n\n\t\tBooking No.\tFlight No.\tClass\t\t     Meal\t\tRow\t    Seat\n\n");	
				while(fread(&userticket,sizeof(tickets),1,*tickptr)==1)
				{
					if(userticket.bookno==currentbook.bookno)
					{
						if(tolower(userticket.meal)=='a')
						{
							strcpy(mealstr,"ADULT");
						}
						else
						{
							strcpy(mealstr,"CHILD");
						}
						
						
						if(tolower(userticket.fclass)=='e')
						{
							strcpy(cstr,"ECONOMY CLASS");
						}
						else if(tolower(userticket.fclass)=='f')
						{
							strcpy(cstr,"FIRST CLASS");
						}
						else if(tolower(userticket.fclass)=='b')
						{
							strcpy(cstr,"BUSINESS CLASS");
						}
						
						
						printf("\n\t\t%10d\t%10s\t%10s\t%10s\t%10c\t%10d\n",userticket.bookno,userticket.flightno,cstr,mealstr,65+userticket.rowno,userticket.seatno);	
						Sleep(200);
					}
				}
				Sleep(400);
				printf("\n\n\t\tEnter Y to view another booking, or any other key to exit: ");
				scanf(" %c",&cchoice);
				
				
				if(tolower(cchoice)!='y')
				{
					fclose(*tickptr);
					fclose(*bookptr);
					break;
				}
				else
				{
					fclose(*tickptr);	
				}	
			}
		    }	
		}
		
	}
}

void addbookings(FILE **ptr,FILE **ticketptr,FILE **routeptr,FILE **flightptr,FILE **bookptr,FILE **tickptr,int customernumber,FILE **rankptr)
{
	routes curr_route,checkroute;
	flights checkflight,countflight;
	tickets newticket;
	bookings newbooking,checkbooking;
	customers updatecustomer;
	rankings crank;
	int rinput;
	newbooking.bookcost=0;
	float discount=0;
    int ticketcounter=0,ffull=0;
	char typetick[20],mealchoice;
	int i,j,k,foundcode=0,flfound=0,foundseat=0,retry,sno,count=0;
	int newbookno,bookingval,classtype,ticketsprice,fchecker;
	char userchoice='y',currcode[20],status[20],flightscode[20],mealstring[30],rowtype[30];
	int seatpref,seatcounter=0;
	*routeptr=fopen("RoutesInfo.dat","rb+");
	if(*routeptr==NULL)
	{
		printf("\n\nError opening file\n\n");
		exit(1);
	}
	else
	{
		//display current routes
		fseek(*routeptr,0,SEEK_END);
		if(ftell(*routeptr)==0)
		{
			printf("\n\nNo Routes To Display\n\n");
			fclose(*routeptr);
			exit(1);
		}
		else
		{
			rewind(*routeptr);			
			printf("\n\nNo.\tRoute Code\tOrigin\tDestination\tRoute Price\n\n");
			sno=1;
			while(fread(&curr_route,sizeof(routes),1,*routeptr)==1)
			{
				//currentprice=currroute.routeprice;
				printf("%d\t%s\t%s\t%s\t%d\n\n",sno,curr_route.routecode,curr_route.origin,curr_route.destination,curr_route.routeprice);
				sno++;
			}
			
			printf("\n\n\n\t\tEnter desired route code from above (ORIGIN-DESTINATION): ");
			scanf("%s",currcode);
			while(checkroutecode(currcode)==0)
			{
				printf("\n\n\t\tPlease enter valid route code (ORIGIN-DESTINATION): ");
				scanf("%s",currcode);
			}
			//search routecode
			while(1)
			{
			rewind(*routeptr);
			while(fread(&checkroute,sizeof(routes),1,*routeptr)==1)
			{
				if(strcmp(checkroute.routecode,currcode)==0)
				{
					foundcode=1;
					break;
				}
				else
				{
					foundcode=0;
				}
			}
			
				if(foundcode==0)
				{
					Sleep(300);
					printf("\n\n\t\tRoute Code entered does not exist. Enter 1. to retry, or any other key exit\n\n");
					scanf(" %d",&retry);
					if (retry==1)
					{
						printf("\n\n\n\t\tEnter desired route code from above (ORIGIN-DESTINATION): ");
						scanf("%s",currcode);
						while(checkroutecode(currcode)==0)
						{
							printf("\n\n\t\tIncorrect input! Please enter valid route code (ORIGIN-DESTINATION): ");
							scanf("%s",currcode);
						}
						continue;	
					}					
					else
					{
						fclose(*routeptr);
						break;
					}
					
				}
				else if (foundcode==1)
				{
					*flightptr=fopen("FlightsInfo.dat","rb+");
					if (*flightptr==NULL)
					{
						printf("\n\nError opening file\n\n");
						exit(1);
					}
					else
					{
						
						rewind(*flightptr);	
						fchecker=0;
						while(fread(&countflight,sizeof(flights),1,*flightptr)==1)
						{
							if(strcmp(countflight.froute,currcode)==0)
							{
								fchecker++;
							}
						}
						
						if(fchecker==0)
						{
							printf("\n\n\n\tNo flights currently exist for the route entered!\n\n");
							Sleep(400);
							fclose(*flightptr);
							fclose(*routeptr);
							break;
						}
						
						rewind(*flightptr);
						printf("\n\n\tRoute Code\tFlight Code\tCurrent Capacity \t FULL\n\n");
						
						while(fread(&checkflight,sizeof(flights),1,*flightptr)==1)
						{
							if(strcmp(checkflight.froute,currcode)==0)
							{
								if(checkflight.full==0)
								{
									strcpy(status,"No");
								}
								else
								{
									strcpy(status,"Yes");
								}
								printf("\t%10s\t%10s\t%10d\t%10s\n\n",checkflight.froute,checkflight.flightcode,checkflight.tseats,status);
							}
						}
						
						printf("\n\n\nEnter desired flight code from above (XY-123): ");
						scanf("%s",flightscode);
						checkflightscode(flightscode);
						//search flights
						rewind(*flightptr);
						while(fread(&checkflight,sizeof(flights),1,*flightptr)==1)
						{
							if(strcmp(checkflight.flightcode,flightscode)==0)
							{
								flfound=1;
								break;
							}
							else
							{
								flfound=0;
							}
						}
						if(flfound==0)
						{
							printf("\n\nFlight entered not found.\n\n");
							fclose(*flightptr);
							fclose(*routeptr);
							exit(1);
						}
						else if(flfound==1)
						{
							if((checkflight.full)==1)
							{
								printf("\n\nFlight fully booked! Please try again later\n\n");
								//here
								fclose(*flightptr);
								fclose(*routeptr);
								exit(1);
							}
							else
							{
								*bookptr=fopen("BookingInfo.dat","ab+");
								if(*bookptr==NULL)
								{
									printf("\n\nError opening file\n\n");
									fclose(*flightptr);
									fclose(*routeptr);
									exit(1);
								}
								else
								{
									newbookno=2100;
									fseek(*bookptr,0,SEEK_END);
									if(ftell(*bookptr)==0)
									{
										bookingval=newbookno;
										newbooking.bookno=bookingval;
										strcpy(newbooking.origin,checkroute.origin);
										strcpy(newbooking.destination,checkroute.destination);
										newbooking.cnum=customernumber;
										*tickptr=fopen("TicketingInformation.dat","ab+");
										if(*tickptr==NULL)
										{		
											printf("\n\nError opening file\n\n");
											fclose(*bookptr);
											fclose(*flightptr);
											fclose(*routeptr);
											exit(1);
										}
										else
										{
											userchoice='y';
											ticketcounter=0;
											while((checkflight.full)==0 && (tolower(userchoice)=='y'))
											{
												rewind(*tickptr);
												newticket.bookno=newbooking.bookno;
												strcpy(newticket.flightno,checkflight.flightcode);
												//loop needed for re-entry of class
												while(1)
												{
												ffull=0;
												seatcounter=0;
												printf("\n\n\t1. Economy Class\n\t2. First Class\n\t3. Business Class\n\tEnter desired seat class:  ");
												scanf(" %d",&classtype);
												while(classtype<1 || classtype>3)
												{
													printf("\n\n\tInvalid seat type! Enter 1, 2, or 3 for desired seat class:  ");
													scanf(" %d",&classtype);
												
												}
												if (classtype==1)
												{
													newticket.fclass='e';
													*ticketptr=fopen("TicketsPrice.txt","r+");
													if(*ticketptr==NULL)
													{
														printf("\n\nError opening file\n\n");
														fclose(*ticketptr);
														fclose(*bookptr);
														fclose(*flightptr);
														fclose(*routeptr);
														exit(1);
													}
													else
													{
														fscanf(*ticketptr,"%s %d",typetick,&ticketsprice);
														//newbooking.bookcost=(newbooking.bookcost)+ticketsprice;
													}
													fclose(*ticketptr);
												}
												else if(classtype==2)
												{
													newticket.fclass='f';
													*ticketptr=fopen("TicketsPrice.txt","r+");
													if(*ticketptr==NULL)
													{
														printf("\n\nError opening file\n\n");
														fclose(*ticketptr);
														fclose(*bookptr);
														fclose(*flightptr);
														fclose(*routeptr);
														exit(1);
													}
													else
													{
														fscanf(*ticketptr,"%s %d",typetick,&ticketsprice);
														fscanf(*ticketptr,"%s %d",typetick,&ticketsprice);
														//newbooking.bookcost=(newbooking.bookcost)+ticketsprice;
													}
													fclose(*ticketptr);
												}
												else if(classtype==3)
												{
													newticket.fclass='b';
													*ticketptr=fopen("TicketsPrice.txt","r+");
													if(*ticketptr==NULL)
													{
														printf("\n\nError opening file\n\n");
														fclose(*ticketptr);
														fclose(*bookptr);
														fclose(*flightptr);
														fclose(*routeptr);
														exit(1);
													}
													else
													{
														fscanf(*ticketptr,"%s %d",typetick,&ticketsprice);
														fscanf(*ticketptr,"%s %d",typetick,&ticketsprice);
														fscanf(*ticketptr,"%s %d",typetick,&ticketsprice);
														//newbooking.bookcost=(newbooking.bookcost)+ticketsprice;
													}
													fclose(*ticketptr);
												}
												
												printf("\n\nEnter meal plan for seat (A: Adult, C: Child): ");
												scanf(" %c",&mealchoice);
												while(tolower(mealchoice)!='a' && tolower(mealchoice)!='c')
												{
													printf("\n\nInvalid meal choice entered. Enter meal plan for seat (A: Adult, C: Child): ");
													scanf(" %c",&mealchoice);
												}
												newticket.meal=mealchoice;
															
												if(tolower(mealchoice)=='a')
												{
													strcpy(mealstring,"ADULT");
												}
												else
												{
													strcpy(mealstring,"CHILD");
												}
												
												printf("\n\n\tEnter Seat Preference:\n\t\t1. Aisle\n\t\t2. Window...");
												scanf("%d",&seatpref);
												while(seatpref<1 || seatpref>2)
												{
													printf("\n\tInvalid entry! Enter   1   for (Aisle), or   2   for (Window): ");
													scanf("%d",&seatpref);
												}
												if(seatpref==1)
												{
													for(i=1;i<3;i++)
													{
														if(newticket.fclass=='e')
														{
															seatcounter++;
															for(j=0;j<30;j++)
															{
														   		
																if((checkflight.seats)[i][j]==0)
																{
																	(checkflight.seats)[i][j]=1;
																	checkflight.tseats=(checkflight.tseats)-1;
																	if (checkflight.tseats==0)
																	{
																		checkflight.full=1;
																	}
																	newticket.rowno=i;
																	newticket.seatno=j;
																	foundseat=1;
																	break;
																}
																else
																foundseat=0;
					
															}
															if (foundseat==1)
															break;
															else
															{
																if(seatcounter==2)
																{
																	Sleep(300);
																	printf("\n\n\tNo space available in Economy Aisle(0-29),\n\tNow Checking For Upgrade to Business Class (30-39) ...\n\n\n");
																	for(k=1;k<3;k++)
																	{
																		for(j=30;j<40;j++)
																		{
																			if((checkflight.seats)[k][j]==0)
																			{
																				(checkflight.seats)[k][j]=1;
																				checkflight.tseats=(checkflight.tseats)-1;
																				if (checkflight.tseats==0)
																				{
																					checkflight.full=1;
																				}
																				newticket.rowno=k;
																				newticket.seatno=j;
																				foundseat=1;
																				break;
																			}
																			else
																			foundseat=0;	
																		}
																		if(foundseat==1)
																		break;
																	}
																	if(foundseat==0)
																	{
																		ffull=1;
																		printf("\n\n\tBusiness (Aisle) fully booked! Choose another class type...\n\n");
																		break;
																	}
																	else
																	break;	
																}
															}
														}
														else if(newticket.fclass=='b')
														{
															for(j=30;j<40;j++)
															{
																if((checkflight.seats)[i][j]==0)
																{
																	(checkflight.seats)[i][j]=1;
																	checkflight.tseats=(checkflight.tseats)-1;
																	if (checkflight.tseats==0)
																	{
																		checkflight.full=1;
																	}
																	newticket.rowno=i;
																	newticket.seatno=j;
																	foundseat=1;
																	break;
																}
																else
																foundseat=0;
															}
															if (foundseat==1)
															break;	
														}
														else if(newticket.fclass=='f')
														{
															for(j=40;j<50;j++)
															{
																if((checkflight.seats)[i][j]==0)
																{
																	(checkflight.seats)[i][j]=1;
																	checkflight.tseats=(checkflight.tseats)-1;
																	if (checkflight.tseats==0)
																	{
																		checkflight.full=1;
																	}
																	newticket.rowno=i;
																	newticket.seatno=j;
																	foundseat=1;
																	break;
																}
																else
																foundseat=0;
															}
															if (foundseat==1)
															break;	
														}
													}
													
													if(ffull==1)
													continue;
													if (foundseat==1)
													break;
													else
													{
														printf("\n\n\tRow for %s class completely booked! Enter another seat type...\n\n",typetick);
														continue;
													}																
												}
else if(seatpref==2)
{
	for(i=0;i<4;i+=3)
	{
		if(newticket.fclass=='e')
		{
			seatcounter++;
			for(j=0;j<30;j++)
			{
													   		
			if((checkflight.seats)[i][j]==0)
			{
				(checkflight.seats)[i][j]=1;
				checkflight.tseats=(checkflight.tseats)-1;
				if (checkflight.tseats==0)
				{
					checkflight.full=1;
				}
				newticket.rowno=i;
				newticket.seatno=j;
				foundseat=1;
				break;
			}
			else
			foundseat=0;
			
			}
			if (foundseat==1)
			break;
			else
			{
				if(seatcounter==2)
				{
					Sleep(300);
					printf("\n\n\tNo space available in Economy Window(0-29),\n\tNow Checking For Upgrade to Business Class (30-39) ...\n\n\n");
					for(k=0;k<4;k+=3)
					{
						for(j=30;j<40;j++)
						{
							if((checkflight.seats)[k][j]==0)
							{
								(checkflight.seats)[k][j]=1;
								checkflight.tseats=(checkflight.tseats)-1;
								if (checkflight.tseats==0)
								{
									checkflight.full=1;
								}
								newticket.rowno=k;
								newticket.seatno=j;
								foundseat=1;
								break;
							}
							else
							foundseat=0;	
						}
						if(foundseat==1)
						break;
					}
					if(foundseat==0)
					{
						ffull=1;
						printf("\n\n\tBusiness (Window) fully booked! Choose another class type...\n\n");
						break;
					}
					else
					break;	
				}
			}
		}
		else if(newticket.fclass=='b')
		{
			for(j=30;j<40;j++)
			{
				if((checkflight.seats)[i][j]==0)
				{
					(checkflight.seats)[i][j]=1;
					checkflight.tseats=(checkflight.tseats)-1;
					if (checkflight.tseats==0)
					{
						checkflight.full=1;
					}
					newticket.rowno=i;
					newticket.seatno=j;
					foundseat=1;
					break;
				}
				else
				foundseat=0;
			}
			if (foundseat==1)
			break;	
		}
		else if(newticket.fclass=='f')
		{
			for(j=40;j<50;j++)
			{
				if((checkflight.seats)[i][j]==0)
				{
					(checkflight.seats)[i][j]=1;
					checkflight.tseats=(checkflight.tseats)-1;
					if (checkflight.tseats==0)
					{
						checkflight.full=1;
					}
					newticket.rowno=i;
					newticket.seatno=j;
					foundseat=1;
					break;
				}
				else
				foundseat=0;
			}
			if (foundseat==1)
			break;	
		}
	}
													
	if(ffull==1)
	continue;
	if (foundseat==1)
	break;
	else
	{
		printf("\n\n\tRow for %s class completely booked! Enter another seat type...\n\n",typetick);
		continue;
	}																
}
												/*if(seatpref==1)
												{
													for(i=1;i<3;i++)
													{
													  
														if(newticket.fclass=='e')
														{
														  seatcounter++;
															for(j=0;j<30;j++)
													   		{
													   		
																if((checkflight.seats)[i][j]==0)
																{
																	(checkflight.seats)[i][j]=1;
																	checkflight.tseats=(checkflight.tseats)-1;
																	if (checkflight.tseats==0)
																	{
																		checkflight.full=1;
																	}
																	newticket.rowno=i;
																	newticket.seatno=j;
																	foundseat=1;
																	break;
																}
																else
																foundseat=0;
														  }
														  if (foundseat==1)
														  break;
														  else
														  {
															   
														  }
													  }
													}
																
												}
												for(i=0;i<4;i++)
												{
													for(j=0;j<50;j++)
													{
														if((checkflight.seats)[i][j]==0)
														{
															(checkflight.seats)[i][j]=1;
															checkflight.tseats=(checkflight.tseats)-1;
															if (checkflight.tseats==0)
															{
																checkflight.full=1;
															}
															newticket.rowno=i;
															newticket.seatno=j;
															foundseat=1;
															break;
														}
														else
														foundseat=0;
													}
													if (foundseat==1)
													break;
												}*/
												}
												newbooking.bookcost=(newbooking.bookcost)+ticketsprice;
												fseek(*flightptr,(long int)-sizeof(flights),SEEK_CUR);
												fwrite(&checkflight,sizeof(flights),1,*flightptr);
												fseek(*tickptr,0,SEEK_END);
												fwrite(&newticket,sizeof(tickets),1,*tickptr);
												
												if(newticket.rowno==1 || newticket.rowno==2)
												{
													strcpy(rowtype,"Aisle");
												}
												else
												{
													strcpy(rowtype,"Window");
												}
												
												printf("\n\n\t*****BOARDING PASSS*****\n\n");
												
												printf("\n\tFlight No.: %s\n\tSeat Type: %s\n\tMeal Type: %s\n\tRow: %c\n\tSeat No.: %d\n\tRow Type: %s\n\n\n",newticket.flightno,typetick,mealstring,65+newticket.rowno,newticket.seatno,rowtype);
												
												printf("\n\tPress any key to continue...\n");
												getch();
																								
												if(checkflight.full==1)
												{
												Sleep(400);
												printf("\n\n\t\tFlight now fully booked!\n\n");
												break;
												}
												
												ticketcounter++;
												printf("Ticket Booked! Enter another ticket? Enter Y/N: ");
												scanf(" %c",&userchoice);
												if(tolower(userchoice)=='n')
												{
													break;
												}
											}
											fclose(*tickptr);
											fseek(*bookptr,0,SEEK_END);
											printf("\n\n\t\tNumber of tickets booked: %d\n",ticketcounter);
											if(ticketcounter<5)
											{
												discount=0;
											}
											else if(ticketcounter>=5 && ticketcounter<=10)
											{
												discount=0.2;
											}
											else
											{
												discount=0.45;
											}
											printf("\n\n\t\tDiscount received for %d tickets: %.2f %%",ticketcounter,discount*100);
											Sleep(350);
											printf("\t\tBooking Cost Before Discount: %d",newbooking.bookcost);
											newbooking.bookcost=(newbooking.bookcost)*(1-discount);
											Sleep(350);
											printf("\n\n\t\tBooking Cost After %.2f %% Discount: %d",discount*100,newbooking.bookcost);
											Sleep(200);
											printf("\n\n\t\tROUTE PRICE for Route Code %s : %d\n\n",checkroute.routecode,checkroute.routeprice);
											Sleep(350);
											printf("\t\tBooking Cost Before Route Charges: %d",newbooking.bookcost);
											newbooking.bookcost=(newbooking.bookcost)+checkroute.routeprice;
											Sleep(350);
											printf("\n\n\t\tBooking Cost After Addition Of Route Charges: %d",newbooking.bookcost);
											Sleep(200);
											fwrite(&newbooking,sizeof(bookings),1,*bookptr);
											Sleep(500);
											
											
											*rankptr=fopen("Rankings.dat","rb+");
											if(*rankptr==NULL)
											{
													printf("\n\nError opening file\n\n");
													fclose(*tickptr);
													fclose(*bookptr);
													fclose(*flightptr);
													fclose(*routeptr);
													exit(1);
											}
											while(fread(&crank,sizeof(rankings),1,*rankptr)==1)
											{
												if (strcmp(crank.fcode,checkflight.flightcode)==0)
												{
													break;
												}
											}
											
											printf("\n\n\t\tHow would you rate your booking experience for Flight %s?\n\n\t\tEnter:\n\n\t\t\t5 - 5 stars\n\t\t\t4 - 4 stars\n\t\t\t3 - 3 stars\n\t\t\t2 - 2 stars\n\t\t\t1 - 1 star\n\n\t\tEnter a value (1-5): ",checkflight.flightcode);
											scanf("%d",&rinput);
											while(rinput<1 || rinput>5)
											{
												printf("\n\n\t\tInvalid Rank Entered! Enter a valid number (1 to 5): ");
												scanf("%d",&rinput);
											}
											crank.pts=(crank.pts)+rinput;
											if(rinput==1)
											crank.review.ones=(crank.review.ones)+1;
											else if (rinput==2)
											crank.review.twos=(crank.review.twos)+1;
											else if (rinput==3)
											crank.review.threes=(crank.review.threes)+1;
											else if (rinput==4)
											crank.review.fours=(crank.review.fours)+1;
											else if (rinput==5)
											crank.review.fives=(crank.review.fives)+1;
											fseek(*rankptr,(long int)-sizeof(rankings),SEEK_CUR);
											fwrite(&crank,sizeof(rankings),1,*rankptr);
											fclose(*rankptr);
											  
											
											printf("\n\n\t\tBooking successfully created!\n\n\tBooking No: %d\n\tBooking Cost: %d\n\tBooking Route: %s - %s\n\n",newbooking.bookno,newbooking.bookcost,newbooking.origin,newbooking.destination);
												//updating customer total cost
												*ptr=fopen("CustomerInfo.dat","rb+");
												if (*ptr==NULL)
												{
													printf("\n\nError opening file\n\n");
													fclose(*tickptr);
													fclose(*bookptr);
													fclose(*flightptr);
													fclose(*routeptr);
													exit(1);
												}
												else
												{
													while(fread(&updatecustomer,sizeof(customers),1,*ptr)==1)
													{
														if(updatecustomer.cnum==customernumber)
														{
															break;
														}
													}
													updatecustomer.costdue=updatecustomer.costdue+newbooking.bookcost;
													fseek(*ptr,(long int)-sizeof(customers),SEEK_CUR);
													fwrite(&updatecustomer,sizeof(customers),1,*ptr);
													printf("\n\nCustomer Total Updated\n\n");
													Sleep(500);
												}
												fclose(*ptr);
											
											
											fclose(*bookptr);
											fclose(*flightptr);
											fclose(*routeptr);
											break;
										}
									}
									else
									{
										count=0;
										//for pre existing booking data
										//assigning booking number (at SEEK_END)
										//fseek(*bookptr,(long int)-sizeof(bookings),SEEK_END);
										//check booking counter
										rewind(*bookptr);
										while(fread(&checkbooking,sizeof(bookings),1,*bookptr)==1)
										{
											if(checkbooking.cnum==customernumber)
											{
												count++;
											}
										}
										
										if(count==6)
										{
											printf("\n\nBooking limit reached. You already have 6 bookings stored.\n\n");
											fclose(*bookptr);
											fclose(*flightptr);
											fclose(*routeptr);
											exit(1);
										}
										else if(count<6)
										{
											rewind(*bookptr);
											fseek(*bookptr,(long int)-sizeof(bookings),SEEK_END);
											fread(&checkbooking,sizeof(bookings),1,*bookptr);
											bookingval=(checkbooking.bookno)+1;
											newbooking.bookno=bookingval;
											strcpy(newbooking.origin,checkroute.origin);
											strcpy(newbooking.destination,checkroute.destination);
											newbooking.cnum=customernumber;
											*tickptr=fopen("TicketingInformation.dat","ab+");
										if(*tickptr==NULL)
										{		
											printf("\n\nError opening file\n\n");
											fclose(*bookptr);
											fclose(*flightptr);
											fclose(*routeptr);
											exit(1);
										}
										else
										{
											userchoice='y';
											ticketcounter=0;
											while((checkflight.full)==0 && (tolower(userchoice)=='y'))
											{
												rewind(*tickptr);
												newticket.bookno=newbooking.bookno;
												strcpy(newticket.flightno,checkflight.flightcode);
												while(1)
												{
												
												printf("\n\n\t1. Economy Class\n\t2. First Class\n\t3. Business Class\n\tEnter desired seat class:  ");
												scanf(" %d",&classtype);
												while(classtype<1 || classtype>3)
												{
													printf("\n\n\tInvalid seat type! Enter 1, 2, or 3 for desired seat class:  ");
													scanf(" %d",&classtype);
												
												}
												if (classtype==1)
												{
													newticket.fclass='e';
													*ticketptr=fopen("TicketsPrice.txt","r+");
													if(*ticketptr==NULL)
													{
														printf("\n\nError opening file\n\n");
														fclose(*ticketptr);
														fclose(*bookptr);
														fclose(*flightptr);
														fclose(*routeptr);
														exit(1);
													}
													else
													{
														fscanf(*ticketptr,"%s %d",typetick,&ticketsprice);
														//newbooking.bookcost=(newbooking.bookcost)+ticketsprice;
													}
													fclose(*ticketptr);
												}
												else if(classtype==2)
												{
													newticket.fclass='f';
													*ticketptr=fopen("TicketsPrice.txt","r+");
													if(*ticketptr==NULL)
													{
														printf("\n\nError opening file\n\n");
														fclose(*ticketptr);
														fclose(*bookptr);
														fclose(*flightptr);
														fclose(*routeptr);
														exit(1);
													}
													else
													{
														fscanf(*ticketptr,"%s %d",typetick,&ticketsprice);
														fscanf(*ticketptr,"%s %d",typetick,&ticketsprice);
														//newbooking.bookcost=(newbooking.bookcost)+ticketsprice;
													}
													fclose(*ticketptr);
												}
												else if(classtype==3)
												{
													newticket.fclass='b';
													*ticketptr=fopen("TicketsPrice.txt","r+");
													if(*ticketptr==NULL)
													{
														printf("\n\nError opening file\n\n");
														fclose(*ticketptr);
														fclose(*bookptr);
														fclose(*flightptr);
														fclose(*routeptr);
														exit(1);
													}
													else
													{
														fscanf(*ticketptr,"%s %d",typetick,&ticketsprice);
														fscanf(*ticketptr,"%s %d",typetick,&ticketsprice);
														fscanf(*ticketptr,"%s %d",typetick,&ticketsprice);
														//newbooking.bookcost=(newbooking.bookcost)+ticketsprice;
													}
													fclose(*ticketptr);
												}
												
												printf("\n\nEnter meal plan for seat (A. Adult, C: Child): ");
												scanf(" %c",&mealchoice);
												while(tolower(mealchoice)!='a' && tolower(mealchoice)!='c')
												{
													printf("\n\nInvalid meal choice entered. Enter meal plan for seat (A. Adult, C: Child): ");
													scanf(" %c",&mealchoice);
												}
												newticket.meal=mealchoice;
												
												if(tolower(mealchoice)=='a')
												{
													strcpy(mealstring,"ADULT");
												}
												else
												{
													strcpy(mealstring,"CHILD");
												}
												printf("\n\n\tEnter seat preference:\n\n\t\t1. Aisle\n\t\t2. Window...");
												scanf("%d",&seatpref);
												if(seatpref==1)
												{
													for(i=1;i<3;i++)
													{
														if(newticket.fclass=='e')
														{
															seatcounter++;
															for(j=0;j<30;j++)
															{
														   		
																if((checkflight.seats)[i][j]==0)
																{
																	(checkflight.seats)[i][j]=1;
																	checkflight.tseats=(checkflight.tseats)-1;
																	if (checkflight.tseats==0)
																	{
																		checkflight.full=1;
																	}
																	newticket.rowno=i;
																	newticket.seatno=j;
																	foundseat=1;
																	break;
																}
																else
																foundseat=0;
					
															}
															if (foundseat==1)
															break;
															else
															{
																if(seatcounter==2)
																{
																	Sleep(300);
																	printf("\n\n\tNo space available in Economy Aisle(0-29),\n\tNow Checking For Upgrade to Business Class (30-39) ...\n\n\n");
																	for(k=1;k<3;k++)
																	{
																		for(j=30;j<40;j++)
																		{
																			if((checkflight.seats)[k][j]==0)
																			{
																				(checkflight.seats)[k][j]=1;
																				checkflight.tseats=(checkflight.tseats)-1;
																				if (checkflight.tseats==0)
																				{
																					checkflight.full=1;
																				}
																				newticket.rowno=k;
																				newticket.seatno=j;
																				foundseat=1;
																				break;
																			}
																			else
																			foundseat=0;	
																		}
																		if(foundseat==1)
																		break;
																	}
																	if(foundseat==0)
																	{
																		ffull=1;
																		printf("\n\n\tBusiness (Aisle) fully booked! Choose another class type...\n\n");
																		break;
																	}
																	else
																	break;	
																}
															}
														}
														else if(newticket.fclass=='b')
														{
															for(j=30;j<40;j++)
															{
																if((checkflight.seats)[i][j]==0)
																{
																	(checkflight.seats)[i][j]=1;
																	checkflight.tseats=(checkflight.tseats)-1;
																	if (checkflight.tseats==0)
																	{
																		checkflight.full=1;
																	}
																	newticket.rowno=i;
																	newticket.seatno=j;
																	foundseat=1;
																	break;
																}
																else
																foundseat=0;
															}
															if (foundseat==1)
															break;	
														}
														else if(newticket.fclass=='f')
														{
															for(j=40;j<50;j++)
															{
																if((checkflight.seats)[i][j]==0)
																{
																	(checkflight.seats)[i][j]=1;
																	checkflight.tseats=(checkflight.tseats)-1;
																	if (checkflight.tseats==0)
																	{
																		checkflight.full=1;
																	}
																	newticket.rowno=i;
																	newticket.seatno=j;
																	foundseat=1;
																	break;
																}
																else
																foundseat=0;
															}
															if (foundseat==1)
															break;	
														}
													}
													
													if(ffull==1)
													continue;
													if (foundseat==1)
													break;
													else
													{
														printf("\n\n\tRow for %s class completely booked! Enter another seat type...\n\n",typetick);
														continue;
													}																
												}
else if(seatpref==2)
{
	for(i=0;i<4;i+=3)
	{
		if(newticket.fclass=='e')
		{
			seatcounter++;
			for(j=0;j<30;j++)
			{
													   		
			if((checkflight.seats)[i][j]==0)
			{
				(checkflight.seats)[i][j]=1;
				checkflight.tseats=(checkflight.tseats)-1;
				if (checkflight.tseats==0)
				{
					checkflight.full=1;
				}
				newticket.rowno=i;
				newticket.seatno=j;
				foundseat=1;
				break;
			}
			else
			foundseat=0;
			
			}
			if (foundseat==1)
			break;
			else
			{
				if(seatcounter==2)
				{
					Sleep(300);
					printf("\n\n\tNo space available in Economy Window(0-29),\n\tNow Checking For Upgrade to Business Class (30-39) ...\n\n\n");
					for(k=0;k<4;k+=3)
					{
						for(j=30;j<40;j++)
						{
							if((checkflight.seats)[k][j]==0)
							{
								(checkflight.seats)[k][j]=1;
								checkflight.tseats=(checkflight.tseats)-1;
								if (checkflight.tseats==0)
								{
									checkflight.full=1;
								}
								newticket.rowno=k;
								newticket.seatno=j;
								foundseat=1;
								break;
							}
							else
							foundseat=0;	
						}
						if(foundseat==1)
						break;
					}
					if(foundseat==0)
					{
						ffull=1;
						printf("\n\n\tBusiness (Window) fully booked! Choose another class type...\n\n");
						break;
					}
					else
					break;	
				}
			}
		}
		else if(newticket.fclass=='b')
		{
			for(j=30;j<40;j++)
			{
				if((checkflight.seats)[i][j]==0)
				{
					(checkflight.seats)[i][j]=1;
					checkflight.tseats=(checkflight.tseats)-1;
					if (checkflight.tseats==0)
					{
						checkflight.full=1;
					}
					newticket.rowno=i;
					newticket.seatno=j;
					foundseat=1;
					break;
				}
				else
				foundseat=0;
			}
			if (foundseat==1)
			break;	
		}
		else if(newticket.fclass=='f')
		{
			for(j=40;j<50;j++)
			{
				if((checkflight.seats)[i][j]==0)
				{
					(checkflight.seats)[i][j]=1;
					checkflight.tseats=(checkflight.tseats)-1;
					if (checkflight.tseats==0)
					{
						checkflight.full=1;
					}
					newticket.rowno=i;
					newticket.seatno=j;
					foundseat=1;
					break;
				}
				else
				foundseat=0;
			}
			if (foundseat==1)
			break;	
		}
	}
													
	if(ffull==1)
	continue;
	if (foundseat==1)
	break;
	else
	{
		printf("\n\n\tRow for %s class completely booked! Enter another seat type...\n\n",typetick);
		continue;
	}																
}
												/*for(i=0;i<4;i++)
												{
													for(j=0;j<50;j++)
													{
														if((checkflight.seats)[i][j]==0)
														{
															(checkflight.seats)[i][j]=1;
															checkflight.tseats=(checkflight.tseats)-1;
															if (checkflight.tseats==0)
															{
																checkflight.full=1;
															}
															newticket.rowno=i;
															newticket.seatno=j;
															foundseat=1;
															break;
														}
														else
														foundseat=0;
													}
													if (foundseat==1)
													break;
												}*/}
												newbooking.bookcost=(newbooking.bookcost)+ticketsprice;
												fseek(*flightptr,(long int)-sizeof(flights),SEEK_CUR);
												fwrite(&checkflight,sizeof(flights),1,*flightptr);
												fseek(*tickptr,0,SEEK_END);
												fwrite(&newticket,sizeof(tickets),1,*tickptr);
												if((newticket.rowno+1)%2==0)
												{
													strcpy(rowtype,"Aisle");
												}
												else
												{
													strcpy(rowtype,"Window");
												}
												Sleep(200);
												printf("\n\n\t*****BOARDING PASSS*****\n\n");
												printf("\n\tFlight No.: %s\n\tSeat Type: %s\n\tMeal Type: %s\n\tRow No.: %d\n\tSeat No.: %d\n\tRow Type: %s\n\n\n",newticket.flightno,typetick,mealstring,newticket.rowno,newticket.seatno,rowtype);
																								
												if(checkflight.full==1)
												{
												printf("\n\nFlight now fully booked!\n\n");
												Sleep(400);
												break;
												}
												
												ticketcounter++;
												printf("Ticket Booked! Enter another ticket? Enter Y/N: ");
												scanf(" %c",&userchoice);
												if(tolower(userchoice)=='n')
												{
													break;
												}
											}
											fclose(*tickptr);
											fseek(*bookptr,0,SEEK_END);
											
									
											printf("\n\n\t\tNumber of tickets booked: %d\n",ticketcounter);
											if(ticketcounter<5)
											{
												discount=0;
											}
											else if(ticketcounter>=5 && ticketcounter<=10)
											{
												discount=0.2;
											}
											else
											{
												discount=0.45;
											}
											Sleep(300);
											printf("\n\n\t\tDiscount received for %d ticket(s): %.2f %%",ticketcounter,discount*100);
											printf("\t\tBooking Cost Before Discount: %d",newbooking.bookcost);
											newbooking.bookcost=(newbooking.bookcost)*(1-discount);
											Sleep(350);
											printf("\n\n\t\tBooking Cost After %.2f %% Discount: %d",discount*100,newbooking.bookcost);
											Sleep(200);
											printf("\n\n\t\tROUTE PRICE for Route Code %s : %d\n\n",checkroute.routecode,checkroute.routeprice);
											Sleep(350);					
											printf("\t\tBooking Cost Before Route Charges: %d",newbooking.bookcost);
											newbooking.bookcost=(newbooking.bookcost)+checkroute.routeprice;
											Sleep(350);
											printf("\n\n\t\tBooking Cost After Addition Of Route Charges: %d",newbooking.bookcost);
											Sleep(200);
											
											fwrite(&newbooking,sizeof(bookings),1,*bookptr);
											Sleep(300);
											//update rankings
											*rankptr=fopen("Rankings.dat","rb+");
											if(*rankptr==NULL)
											{
													printf("\n\nError opening file\n\n");
													fclose(*tickptr);
													fclose(*bookptr);
													fclose(*flightptr);
													fclose(*routeptr);
													exit(1);
											}
											while(fread(&crank,sizeof(rankings),1,*rankptr)==1)
											{
												if (strcmp(crank.fcode,checkflight.flightcode)==0)
												{
													break;
												}
											}
											
											printf("\n\n\t\tHow would you rate your booking experience for Flight %s?\n\n\t\tEnter:\n\n\t\t\t5 - 5 stars\n\t\t\t4 - 4 stars\n\t\t\t3 - 3 stars\n\t\t\t2 - 2 stars\n\t\t\t1 - 1 star\n\n\t\tEnter a value (1-5): ",checkflight.flightcode);
											scanf("%d",&rinput);
											while(rinput<1 || rinput>5)
											{
												printf("\n\n\t\tInvalid Rank Entered! Enter a valid number (1 to 5): ");
												scanf("%d",&rinput);
											}
											crank.pts=(crank.pts)+rinput;
											if(rinput==1)
											crank.review.ones=(crank.review.ones)+1;
											else if (rinput==2)
											crank.review.twos=(crank.review.twos)+1;
											else if (rinput==3)
											crank.review.threes=(crank.review.threes)+1;
											else if (rinput==4)
											crank.review.fours=(crank.review.fours)+1;
											else if (rinput==5)
											crank.review.fives=(crank.review.fives)+1;
											fseek(*rankptr,(long int)-sizeof(rankings),SEEK_CUR);
											fwrite(&crank,sizeof(rankings),1,*rankptr);
											fclose(*rankptr);
											  
											printf("\n\nBooking successfully created!\n\tBooking No: %d\n\tBooking Cost: %d\n\tBooking Route: %s - %s\n\n",newbooking.bookno,newbooking.bookcost,newbooking.origin,newbooking.destination);
										    printf("\n\n\t\tPress any key to continue...\n\n");
										    getch();
												//updating customer total cost
												*ptr=fopen("CustomerInfo.dat","rb+");
												if (*ptr==NULL)
												{
													printf("\n\nError opening file\n\n");
													fclose(*tickptr);
													fclose(*bookptr);
													fclose(*flightptr);
													fclose(*routeptr);
													exit(1);
												}
												else
												{
													while(fread(&updatecustomer,sizeof(customers),1,*ptr)==1)
													{
														if(updatecustomer.cnum==customernumber)
														{
															break;
														}
													}
													updatecustomer.costdue=updatecustomer.costdue+newbooking.bookcost;
													fseek(*ptr,(long int)-sizeof(customers),SEEK_CUR);
													fwrite(&updatecustomer,sizeof(customers),1,*ptr);
													Sleep(200);
													printf("\n\nCustomer Total Updated\n\n");
													Sleep(500);
												}
												fclose(*ptr);
											
											
											fclose(*bookptr);
											fclose(*flightptr);
											fclose(*routeptr);
											break;
										}
											
										}
									}
								}
							}
						}
					}
				}
			}
		}			
	}
}

void checkflightscode(char* fcode)
{
	//function returns valid flight code
	int i,len,flag=1;
	while(strlen(fcode)!=6)
	{
		printf("\n\nCode too short or long. Enter 6 digit flight code (XY-123): ");
		scanf("%s",fcode);
	}
	while(1)
	{
	for(i=0;i<2;i++)
	{
		if((fcode[i]<'a' || fcode[i]>'z') && (fcode[i]<'A' || fcode[i]>'Z'))
		{
			flag=1;	
			break;
		}		
		else
		flag=0;
	}
	if(flag==0)
	{
		printf("\n\n***Valid Code Entered***\n\n");
		break;
	}
	else if (flag==1)
	{
		printf("\n\nIncorrect Code Entered! Enter valid code of format (XY-123): ");
		scanf("%s",fcode);
		while(strlen(fcode)!=6)
		{
			printf("\n\nCode too short or long. Enter 6 digit flight code (XY-123): ");
			scanf("%s",fcode);
		}
	}
	}
}

void viewaccountinfo(FILE **ptr,int cnumber)
{
	customers vcustomer; //unameupass 30c; fnamelname 40c
	int cfound=0,i;
	char change='n',ch1;
	char newpass[30],oldpass[30];
	*ptr=fopen("CustomerInfo.dat","rb+");
	if (*ptr==NULL)
	{
		printf("\n\nAccount Information could not be displayed\n\n");
		exit(1);
	}
	else
	{
		while(fread(&vcustomer,sizeof(customers),1,*ptr)==1)
		{
			if (vcustomer.cnum==cnumber)
			{
				cfound=1;
				break;
			}
			else
			cfound=0;
		}
		if(cfound==1) 
		{
			strcpy(oldpass,vcustomer.upass);
			printf("\n\n\t\tCustomer Name: %s %s\n\t\tCustomer ID: %d\n\t\tUsername: %s\n\t\tPassword: %s\n\t\tCost Due: %d\n\t\tCredit Card Number: %d\n\n",vcustomer.fname,vcustomer.lname,cnumber,vcustomer.uname,vcustomer.upass,vcustomer.costdue,vcustomer.cardnum);
			Sleep(500);
			while(1)
			{
				Sleep(300);
				printf("\n\n\t\t********************** Update password ? **********************\n\n\t\tEnter Y/N: ");
				scanf(" %c",&change);
				if (tolower(change)=='n')
				{
					printf("\n\nPassword unchanged.\n\n");
					break;
				}
				else if(tolower(change)=='y')
				{
					printf("\n\nEnter your new Password(Limit: 30 characters)(Backspace not allowed): ");
     				for(i=0; i<30; i++)
     				{
             			ch1=getch();
             			newpass[i]=ch1;
             			if(ch1!=13)      //13 is ASCII of Enter key
                   		printf("*");
             			if(ch1 == 13)
                   		break;
      				}			
      				newpass[i]='\0';
      				strcpy(vcustomer.upass,newpass);
      				fseek(*ptr,(long int)-sizeof(customers),SEEK_CUR);
      				fwrite(&vcustomer,sizeof(customers),1,*ptr);
      				printf("\n\nPassword successfully updated!\n\nOld password: %s\n\nNew password: %s\n\n",oldpass,newpass);
      				break;
				}
				else
				{
					printf("\n\nPlease Enter Valid Choice.\n\n");
				}
			}
			Sleep(500);
			fclose(*ptr);
		}
		else
		{
			printf("\n\nAcccount Does Not Exist!\n\n");
			fclose(*ptr);
		}
	}
	
}

void displayusermenu()
{
	printf("\n\n\n\t\t\t\n\n\t\t\t1. Create Booking\n\n\t\t\t2. View Account Information\n\n\t\t\t3. View Updated Ticket Prices\n\n\t\t\t4. View Route Information\n\n\t\t\t5. View Booking Information\n\n\t\t\t6. FEEDBACK PORTAL\n\n\t\t\t7. View Updated Flight Rankings\n\n\t\t\t8. Logout\n\n");
	Sleep(200);
	printf("\n\n\n\t\t\t\n\n\t\t\tPlease Enter Your Choice: ");
}

void changeticketprice(FILE **ticketptr)
{
	char ticktype[20];
	int price;
	
	*ticketptr=fopen("TicketsPrice.txt","w+");
	if(*ticketptr==NULL)
	{
		printf("\n\nError opening file\n\n");
		exit(1);
	}
	else
	{
			fseek(*ticketptr,0,SEEK_END);
			printf("\n\n\t\tEnter ticket price for Economy Class(Min: 5000, Max: 15000): ");
			scanf("%d",&price);
			while (price<5000 || price>15000)
			{
				printf("\n\t\tInvalid price entered. Enter a valid price: ");
				scanf("%d",&price);	
			}			
			fprintf(*ticketptr,"%s %d\n","Economy",price);
			printf("\n\n\t\tEnter ticket price for First Class(Min: 15000, Max: 70000): ");
			scanf(" %d",&price);
				while (price<15000 || price>70000)
			{
				printf("\n\t\tInvalid price entered. Enter a valid price: ");
				scanf(" %d",&price);	
			}	
			fprintf(*ticketptr,"%s %d\n","First",price);
			printf("\n\n\t\tEnter ticket price for Business(Min: 70000, Max: 100000): ");
			scanf(" %d",&price);
				while (price<70000 || price>100000)
			{
				printf("\n\t\tInvalid price entered. Enter a valid price: ");
				scanf(" %d",&price);	
			}
			fprintf(*ticketptr,"%s %d\n","Business",price);
			printf("\n\nPrices succesfully updated\n");
			fclose(*ticketptr);
		
	}
}

void viewticketprice(FILE **ticketptr)
{
	char typetick[20];
	int ticketsprice;
	*ticketptr=fopen("TicketsPrice.txt","r+");
	if(*ticketptr==NULL)
	{
		printf("\n\nError opening file\n\n");
		exit(1);
	}
	else
	{
		printf("\n\n\t\t\t     |Class\t     |Price|\n\t\t\t************************\n\n");
		Sleep(500);
		while(fscanf(*ticketptr,"%s %d",typetick,&ticketsprice)!=EOF)
		{
			Sleep(200);
			printf("\t\t\t|%10s|\t%10d|\n",typetick,ticketsprice);
		}
		printf("\n\t\t      ************************\n\n");
		printf("\nPress any key to continue\n");
		getch();
		fclose(*ticketptr);
	}
}

void viewrouteprice(FILE **routeptr)
{
	int currentprice=0,sno=1;
	routes currentroute;
	*routeptr=fopen("RoutesInfo.dat","rb+");
	if (*routeptr==NULL)
	{
		printf("\n\nError opening file. No routes to display\n\n");
	}
	else
	{
		printf("\n        +======================================================================+\n");
		printf("\t|S.No.|\t  |Route Code|\t | Origin |\t |Destination|\t  |Route Price|\n");
		printf("        +======================================================================+\n");
		while(fread(&currentroute,sizeof(routes),1,*routeptr)==1)
		{
			Sleep(200);
			currentprice=currentroute.routeprice;
			printf("   %10d\t%10s\t%10s\t%10s\t%10d\n",sno,currentroute.routecode,currentroute.origin,currentroute.destination,currentprice);
			sno++;
		}
		printf("        +======================================================================+\n\n");
		Sleep(400);
		printf("\n\n\tPress any key to continue...");
		getch();
		fclose(*routeptr);
	}	
}


int checkroutecode(char* code)
{
	int i,count=0;
	int len=strlen(code);
	//ORIGIN-DESTINATION
	for(i=0;i<len;i++)
	{
		if (code[i]=='-')
		count++;
	}
	if (count==0)
	{
		return 0;
	}
	else
	return 1;
}



void addflight(FILE **flightptr,FILE **routeptr,FILE **rankptr)
{
	/**routeptr=fopen("RoutesInfo.dat","rb+");
	if (*routeptr==NULL)
	{
		printf("\n\nError opening file.\n\n");
	}
	else
	{

	}*/
	int i,j,k,l,found=0,found1=0,flag=1,userchoice=1,ffound;
	routes croute;
	int serialno=0;
	flights newflight,cflight;
	char currentcode[20];
	rankings newrank;
	*flightptr=fopen("FlightsInfo.dat","ab+");
	if(*flightptr!=NULL)
	{
	while(userchoice==1)
	{
	system("cls");	
	flag=1;
	fseek(*flightptr,0,SEEK_END);	
	if (ftell(*flightptr)==0)
	{
		printf("\n\n\t\tFirst flight:");
		while(1)
		{
		printf("\n\n\t\tEnter Route Code: ");
		scanf(" %s",currentcode);
		if(checkroutecode(currentcode)==0)
		{
			printf("\n\n\t\tIncorrect route code entered. Enter code again.\n\n");
			
		}
		else
		break;	
		}
		*routeptr=fopen("RoutesInfo.dat","rb+");
		if (*routeptr==NULL)
		{
			printf("\n\n\t\tError opening file\n\n");
			fclose(*flightptr);
			exit(1);
			break;
		}
		else 
		{
			rewind(*routeptr);
				printf("\n\n\t|S.No.|\t  |Route Code|\t   |Origin|\t |Destination|\t  |Route Price|\n");
		printf("    -----------------------------------------------------------------------\n\n");
			while(fread(&croute,sizeof(routes),1,*routeptr)==1)
			{
			printf("\t%10s\t%10s\t%10s\t%10d\n\n",croute.routecode,croute.origin,croute.destination,croute.routeprice);
			if (strcmp(croute.routecode,currentcode)==0)
			{
				ffound=1;
				break;
			}
			else
			{
				ffound=0;
			}
			
			}
			
			if(ffound==1)
			{
			
			strcpy(newflight.froute,currentcode);
			printf("\n\n\n\t\tEnter a unique 6 digit flight code of the following format (XY-123) where Country Code entered first: ");
			scanf(" %s",newflight.flightcode);
			while (strlen(newflight.flightcode)!=6)
			{
				printf("\n\n\t\tInvalid flight code. Please enter valid code: ");
				scanf(" %s",newflight.flightcode);
			}
			while (flag==1)
			{
				for(i=0;i<2;i++)
			{
				if ((newflight.flightcode[i]<'a' || newflight.flightcode[i]>'z') && (newflight.flightcode[i]<'A' || newflight.flightcode[i]>'Z'))
				{
					flag=1;
					break;
				}
				else
				flag=0;
			}
			if (flag==1)
			{
				printf("\n\n\t\tInvalid country  code. enter a valid flight code: ");
				printf("\n\n\t\tEnter a unique 6 digit flight code of the following format (XY-123) where Country Code entered first: ");
				scanf(" %s",newflight.flightcode);
				while (strlen(newflight.flightcode)!=6)
				{
				printf("\n\n\t\tInvalid flight code. Please enter valid code: ");
				scanf(" %s",newflight.flightcode);
				}
			}	
			else
			break;
			}
			newflight.full=0;
			newflight.tseats=200;
			
			for(i=0;i<4;i++)  /*initialising seats*/
			{
				for(j=0;j<50;j++)
				{
					newflight.seats[i][j]=0;
				}
			}
			
			fwrite(&newflight,sizeof(flights),1,*flightptr);
			fclose(*routeptr);
			//add flight to rankings file
				
				*rankptr=fopen("Rankings.dat","ab+");
				strcpy(newrank.fcode,newflight.flightcode);
				newrank.pts=0;
				newrank.review.fives=0;
				newrank.review.fours=0;
				newrank.review.threes=0;
				newrank.review.twos=0;
				newrank.review.ones=0;
				fwrite(&newrank,sizeof(rankings),1,*rankptr);
				fclose(*rankptr);
				
				printf("\n\n\n\t ||Flight-Code|\t|5 stars|\t|4 stars|\t|3 stars|\t|2 stars|\t|1 star|\t|Points||\n\n");
				printf("%10s\t%10d\t%10d\t%10d\t%10d\t%10d\t%10d\n",newrank.fcode,newrank.review.fives,newrank.review.fours,newrank.review.threes,newrank.review.twos,newrank.review.ones,newrank.pts);
				
			printf("\n\n\t\tFlight successfully stored. Add another flight for a route? 1.Yes/2.No\n\t\tEnter your choice: ");
			scanf(" %d",&userchoice);
			if(userchoice==2)
			{
				break;
			}
			
	       }
		   else if (ffound==0)
		   {
		   	printf("\n\n\t\tRoute entered does not exist!\n\n");
			printf("\n\n\t\tFlight not stored. Add another flight for a route? 1.Yes/2.No\n\t\tEnter your choice: ");
			scanf(" %d",&userchoice);
			fclose(*routeptr);
			if (userchoice==2)
			break;	
		   }
			
		}
	}
	else
	{
		*routeptr=fopen("RoutesInfo.dat","rb+");
		if (*routeptr==NULL)
		{
			printf("\n\nError opening file");
			fclose(*flightptr);
			exit(1);
			break;
		}
		rewind(*routeptr);
		serialno=0;
		printf("\n\n\n        +======================================================================+\n");
		printf("\t|S.No.|\t  |Route Code|\t | Origin |\t |Destination|\t  |Route Price|\n");
		printf("        +======================================================================+\n");
		while(fread(&croute,sizeof(routes),1,*routeptr)==1)
		{
			Sleep(200);
			serialno++;
			printf("   %10d\t%10s\t%10s\t%10s\t%10d\n",serialno,croute.routecode,croute.origin,croute.destination,croute.routeprice);
			
		}
		printf("        +======================================================================+\n\n");
		
		while(1)
		{
		printf("\n\n\t\tEnter Route Code: ");
		scanf(" %s",currentcode);
		if(checkroutecode(currentcode)==0)
		{
			printf("\n\n\t\tIncorrect route code entered. Enter code again.\n\n");
			
		}
		else
		break;	
		}
		
		rewind(*routeptr);
		
		while(fread(&croute,sizeof(routes),1,*routeptr)==1)
		{
				if (strcmp(currentcode,croute.routecode)==0)
				{
					found=1;
					break;	
				}
				else
				found=0;			
		}
		
		//{
		
		if (found==1)
		{
			rewind(*routeptr);
			strcpy(newflight.froute,currentcode);
			//flight code
			while(1)
			{
			flag=1;				
			printf("\n\n\t\tEnter a unique 5 digit flight code of the format (XY-123), where Country Code entered first: ");
			scanf(" %s",newflight.flightcode);
			while (strlen(newflight.flightcode)!=6)
			{
				printf("\n\n\t\tInvalid flight code. Please enter valid code: ");
				scanf(" %s",newflight.flightcode);
			}
			while (1)
			{
				for(i=0;i<2;i++)
				{
					if ((newflight.flightcode[i]<'a' || newflight.flightcode[i]>'z') && (newflight.flightcode[i]<'A' || newflight.flightcode[i]>'Z'))
					{
						flag=1;
						break;
					}
					else
					flag=0;
				}
			if (flag==1)
			{
				printf("\n\n\t\tInvalid country  code. enter a valid flight code: ");
				printf("\n\n\t\tEnter a unique 6 digit flight code of the following format (XY-123) where Country Code entered first: ");
				scanf(" %s",newflight.flightcode);
				while (strlen(newflight.flightcode)!=6)
				{
				printf("\n\n\t\tInvalid flight code. Please enter valid code: ");
				scanf(" %s",newflight.flightcode);
				}
			}	
			else
			break;
			}
			rewind(*flightptr);
			while(fread(&cflight,sizeof(flights),1,*flightptr)==1)
			{
				
					if(strcmp(newflight.flightcode,cflight.flightcode)==0)
					{
						found1=1;
						break;
					}
					else
					found1=0;			
			}
			if (found1==1)
			{
				printf("\n\n\t\tFlight code entered already exists! Please try again\n\n");
				continue;
			}
			else
			{
				
				newflight.full=0;
				newflight.tseats=200;
				for(i=0;i<4;i++)  /*initialising seats*/
				{
					for(j=0;j<50;j++)
					{
						newflight.seats[i][j]=0;
					}
				}
				
				fseek(*flightptr,0,SEEK_END);
				fwrite(&newflight,sizeof(flights),1,*flightptr);
				fclose(*routeptr);
				//add flight to rankings file
				
				*rankptr=fopen("Rankings.dat","ab+");
				strcpy(newrank.fcode,newflight.flightcode);
				newrank.pts=0;
				newrank.review.fives=0;
				newrank.review.fours=0;
				newrank.review.threes=0;
				newrank.review.twos=0;
				newrank.review.ones=0;
				fwrite(&newrank,sizeof(rankings),1,*rankptr);
				fclose(*rankptr);
				
				printf("\n\n\n\t ||Flight-Code|\t|5 stars|\t|4 stars|\t|3 stars|\t|2 stars|\t|1 star|\t|Points||\n\n");
				printf("%10s\t%10d\t%10d\t%10d\t%10d\t%10d\t%10d\n",newrank.fcode,newrank.review.fives,newrank.review.fours,newrank.review.threes,newrank.review.twos,newrank.review.ones,newrank.pts);
				
				printf("\n\n\t\tFlight successfully stored. Add another flight for a route? 1.Yes/2.No\n\t\tEnter your choice: ");
				scanf(" %d",&userchoice);
				break;
			}
		}
		if (userchoice==2)
		break;
		}
		else if (found==0)
		{
			printf("\n\n\t\tRoute entered does not exist!\n\n");
			printf("\n\n\t\tFlight not stored. Add another flight for a route? 1.Yes/2.No\n\t\tEnter your choice: ");
			scanf(" %d",&userchoice);
			fclose(*routeptr);
			if (userchoice==2)
			break;
		}
		
	//}
		
			
	}
	
	}
	fclose(*flightptr);
	
}
else
{
	printf("\n\nError opening file.\n");
	exit(1);
}
}


void addroute(FILE **routeptr)
{
	int found=0,found1=0;
	routes newroute,aroute;
	char orig[20],dest[20],rchoice='y',retry='y';
	printf("\n\n\t********************ADD A ROUTE********************");
	printf("\n\n\t\tEnter Origin of Route (No more than 19 characters!): ");
	scanf(" %s",orig);
	printf("\n\n\t\tEnter Destination of Route (No more than 19 characters!): ");
	scanf(" %s",dest);
	*routeptr=fopen("RoutesInfo.dat","ab+");
	if (*routeptr != NULL)
	{
    	fseek (*routeptr, 0, SEEK_END);    
    	if (ftell(*routeptr) == 0)
	 	{
        printf("\n\n\t\tFirst route:");
        strcpy(newroute.destination,dest);
        strcpy(newroute.origin,orig);
    	printf("\n\n\t\tEnter Route code (format: ORIGIN-DESTINATION): ");
     	scanf(" %s",newroute.routecode);
     	while(checkroutecode(newroute.routecode)==0)
     	{
     		printf("\n\n\t\tInvalid route code entered. Enter valid route code: ");
     		scanf(" %s",newroute.routecode);
		}
     	while(1)
		{
			printf("\n\n\t\tEnter Route Price (Not more than 20000 PKR): ");
     		scanf(" %d",&newroute.routeprice);
     		if (newroute.routeprice<=0 || newroute.routeprice>20000)
     		{
     			printf("\n\t\tPlease enter a valid amount\n");
     			scanf(" %d",&newroute.routeprice);
			}
			else
			break;
     	}
     	fwrite(&newroute,sizeof(routes),1,*routeptr);
     	printf("\n\n\t\tRoute successfully entered.\n");
     	Sleep(400);
     	fclose(*routeptr);
		}
		else
		{
			fclose(*routeptr);
			*routeptr=fopen("RoutesInfo.dat","rb+");
			while(rchoice=='Y' || rchoice=='y')
			{	
				found=0;
				rewind(*routeptr);
				while(fread(&aroute,sizeof(routes),1,*routeptr)==1)
				{
				
					if (aroute.origin==orig && aroute.destination==dest)
					{
						found=1;					
						break;		
					}
					else
					found=0;
				}
				if (found==1)
				{
					printf("\n\t\tRoute already exists. Retry? Enter Y/N\n");
					scanf(" %c",&rchoice);
					if (rchoice=='Y' || rchoice=='y')
					{
						printf("\n\n\t\tEnter New Destination of Route: ");
						scanf(" %s",dest);
					}
				}
				else
				{
					
					strcpy(newroute.destination,dest);
        			strcpy(newroute.origin,orig);
        			while(1)
        			{
        				found1=0;
        				printf("\n\n\t\tEnter Route code (format: ORIGIN-DESTINATION): ");
     					scanf(" %s",newroute.routecode);
     					while(checkroutecode(newroute.routecode)==0)
     					{			
     						printf("\n\n\t\tInvalid route code entered. Enter valid route code: ");
     						scanf(" %s",newroute.routecode);
						}
     					rewind(*routeptr);
						while(fread(&aroute,sizeof(routes),1,*routeptr))
						{		
				
							if (strcmp(aroute.routecode,newroute.routecode)==0)
							{
								found1=1;					
								break;		
							}
							else
							found1=0;
						}
						if (found1==1)
						{
						printf("\n\n\t\tRoute code already exists! Retry? Enter Y/N: ");
						scanf(" %c",&retry);
						if (retry=='Y' || retry=='y')
						continue;
						else
						break;
						}
						else if(found1==0)
						break;
					}
					while(1)
						{
							printf("\n\n\t\tEnter Route Price (Not more than 20000 PKR): ");
     						scanf(" %d",&newroute.routeprice);
     						if (newroute.routeprice<=0 || newroute.routeprice>20000)
     						{
     							printf("\n\n\t\tPlease enter a valid amount!\n\n");
							}
							else
							break;
     					}
    				fseek (*routeptr, 0, SEEK_END);
     				fwrite(&newroute,sizeof(routes),1,*routeptr);	
					printf("\n\n\t\tRoute successfully entered.\n");
					Sleep(400);
					printf("\n\n\t\tPress any key to continue");
					getch();
					fclose(*routeptr);
					break; 	
				}
			}		
		}
	}
	else
	{
		printf("\n\nError opening file.\n\n");
		exit(1);
	}

}

void displayadminmenu()
{
	printf("\n\n\n\t1.Add a route\n\t2.Add a flight\n\t3.Display Routes\n\t4.Display Flights\n\t5.View ticket price\n\t6.Update ticket price\n\t7.Manage Customer Accounts\n\t8.Reset Flight Rankings\n\t9.View Current Rankings (Unsorted)\n\t10. Logout\n\tEnter your choice...\n\n\n");
	
}

int getpin()
{
		int pinval;
		printf("\n\n\t\t\t\tPlease Enter 4 DIGIT ACCESS PIN: ");
	    scanf("%d",&pinval);
	    return pinval;
}
void currenttime()
{
  time_t rawtime;
  struct tm * timeinfo;

  time ( &rawtime );
  timeinfo = localtime ( &rawtime );
  printf ( "\t%s\n\n\n", asctime (timeinfo) );

}

int ulogin(FILE **ptr,FILE **fp,char* fname,char* cfname,char* str,int* cval)
{
	char ch1,username[30],password[30],user='Y',searchname[30],c1,searchpassword[30],s1[30],retry='y';
	int choice=0,found,c=3,found1=0,i,ucardnum;
	customers cuser,checkuser;
	while(choice!=3)
	{
	system("cls");
	found=0;
	printf("\n\n1. Sign Up\n2. Login to USER\n3. Exit\n\nEnter choice: ");
	scanf("%d",&choice);
	
	if (choice==1)
	{
		
		*ptr=fopen("CustomerInfo.dat","ab+");
	if (*ptr==NULL)
	{
		printf("Account could not be created at this time. Contact ADMIN.\n");
		return 0;
	}

		
		printf("\n\nEnter your username: ");
		scanf(" %s",username);
		printf("\n\nEnter your First Name: ");
		scanf(" %s",cuser.fname);
		printf("\n\nEnter your Last Name:");
		scanf(" %s",cuser.lname);
		strcpy(cuser.uname,username);
		printf("\n\nEnter you credit card number (6 digit pin): ");
		scanf(" %d",&cuser.cardnum);
		//add code to read last value of cno************
		
		   fseek(*ptr,0,SEEK_END);
		   if (ftell(*ptr)==0)
		   {
				cuser.cnum=cno;
				
		   }
		   else
		   {
		   		fseek(*ptr,(long int)-sizeof(customers),SEEK_END);
		   		fread(&checkuser,sizeof(customers),1,*ptr);
		   		cuser.cnum=(checkuser.cnum)+1;		   		
		   }   
		cuser.costdue=0;
		rewind(*ptr);
		while(fread(&checkuser,sizeof(customers),1,*ptr)==1)
		{
			if(strcmp(checkuser.uname,username)==0)
			{
				printf("\n\nAccount already exists!\n1.Retry or 2. Return: ");
				scanf("%d",&found);						
			}			
		}
		if(found==1)
		{
			continue;
		}
		else if(found==2)
		break;
		else
		{
		
		/*printf("Enter password: ");
		scanf("%s",password);*/
	 printf("\n\nEnter your Password(Limit: 30 characters)(Backspace not allowed): ");
     for(i=0; i<30; i++)
     {
             ch1=getch();
             password[i]=ch1;
      
             if(ch1!=13)      //13 is ASCII of Enter key
                   printf("*");
             if(ch1 == 13)
                   break;
      }
      password[i]='\0';
		
		fseek(*ptr,0,SEEK_END);
		/*fprintf(*fp,"%s %s\n",username,password);
		*ptr = fopen(cfname,"ab+");*/
	if (*ptr==NULL)
	{
		printf("Account could not be created at this time. Contact ADMIN.\n");
		return 0;
	}
		strcpy(cuser.upass,password);
		fwrite(&cuser,sizeof(customers),1,*ptr);
		printf("\nAccount created!\n");
		printf("\n\nPress any key to continue\n\t");
		getch();
		found=0;
		}
	
	fclose(*ptr);
	}
	/*else if (choice==2)
	{
		*fp = fopen(fname,"r+");
		printf("\n\nUsername\tPassword\n");
		while(fscanf(*fp,"%s %s",username,password)!=EOF)
		{
			printf("\n%-10s\t%10s\n",username,password);
		}
		fclose(*fp);
		return 0;
	}*/
	else if (choice==2)
	{
		
		printf("\n\nEnter username: ");
		scanf(" %s",searchname);
		*ptr=fopen(cfname,"rb+");
		
		if (*ptr==NULL)
		{
			printf("\n\nFile could not be opened.\n");
			return 0;
		}
		
		
		while(fread(&checkuser,sizeof(customers),1,*ptr)==1)
		{
			if(strcmp(searchname,checkuser.uname)==0)
			{
				found=1;
				break;
			}
			else
			found=0;			
		}
		if(found==1)
		{
			
			while((retry=='y' || retry=='Y') && c>=1)
			{
			
			rewind(*ptr);
			printf("\n\nEnter password (No more than 30 characters)(Backspace not allowed): ");
			/*scanf("%s",searchpassword);*/
			for(i=0; i<30; i++)
     		{
             ch1=getch();
             searchpassword[i]=ch1;
      
             if(ch1!=13)      //13 is ASCII of Enter key
                   printf("*");
             if(ch1 == 13)
                   break;
      		}
      		 searchpassword[i]='\0';
			
			while(fread(&checkuser,sizeof(customers),1,*ptr)==1)
			{
				if(strcmp(searchpassword,checkuser.upass)==0)
				{
					found1=1;
					/* *ptr=fopen("CustomerInfo.dat","rb+");
					   if (*ptr==NULL)
					   {
					   		printf("\n\nAn Error occurred opening customerinfo.dat\n\n);
					   		fclose(*fp);
					   		return 0;
					   }
					   else
					   {
					   		while(fread(&checkuser,sizeof(customers),1,*ptr))
					   		{
					   			if(strcmp(checkuser.upass,searchpassword)==0)
					   			{
					   				strcpy(str,checkuser.fname);
					   				*cval=(checkuser.cnum);
					   			}
					   		}
					   }
					   fclose(*ptr)   */
					strcpy(str,checkuser.fname);
					*cval=(checkuser.cnum);
					printf("\n\n\t\t***You Are Now Logged In***\n\n");
					printf("\n\n\t\tCustomer Number: %d\n\n",*cval);
					Sleep(500);
					fclose(*ptr);
					return 1;
				}
				else
				found1=0;			
			}
			/*if(found1==1)
			{
				printf("\n\n***Logged In. Exiting module***\n\n");
				return 0;
			}*/
			if(found1==0)
			{
				c--;
				Sleep(500);
				printf("\n\nIncorrect password entered.\n\nAttempts left: %d \n\nRetry? Y, or N to return:  ",c);
				scanf(" %c",&retry);				
			}
			if(retry=='n' || retry=='N')
			break;
		}
	}
	else if(found==0)
	{
		printf("No such user exists!\n");
	}
	fclose(*ptr);		
	}
	else if(choice!=3)
	{
		printf("\n\n\aInvalid input! Enter from 1,2 or 3. Enter 3 to exit.\n\n");
	}
	else if(choice==3)
	{
		return 2;
	}
	}
} 

