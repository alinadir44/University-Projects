
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
		scanf("%d",usechoice);
		while(usechoice<1 || usechoice>2)
		{
			printf("\n\n\t**Invalid Entry!**\n\tEnter:\n\n\t\t1. To Initialise/Reset Flight Rankings For All Flights\n\t\t2. Exit\n\n");
			scanf("%d",usechoice);
		}
		if(usechoice==1)
		{
			printf("\n\n\tALERT! All Flight Rankings and User Ratings(*) Will Now Be Erased/Reset!\n\n\tPress any key to continue");
			getch;
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
			printf("\n\n\tExiting...")
			Sleep(400);
			fclose(*flightptr);
		}
	}
}
