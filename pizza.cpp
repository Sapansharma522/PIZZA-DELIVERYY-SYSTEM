#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>
#include<climits>
using namespace std;
//header files

struct PizzaTypes
{
    int smallQuantity, mediumQuantity, largeQuantity, others, freshPan, cheeseBurst, wheatThinCrust;
};
//structure for defining pizza types

struct PizzaCost
{
    int smallCost, mediumCost, largeCost, freshPanCost, cheeseBurstCost, wheatThinCrustCost;
};
//structure for drfining pizza costs

int partition(vector<int> &v, int s, int e)
{
    int i = s - 1;
    int pivot = v[e];

    for (int j = s; j < e; j++)
    {
        if (v[j] > pivot)
        {
            i++;
            swap(v[i], v[j]);
        }
    }

    swap(v[i + 1], v[e]);
    return i + 1;

}
//partitioning function for quick sort

void quicksort(vector<int> &v, int s, int e)
{
    if (s >= e)
    {
        return;
    }

    int p = partition(v, s, e);
    quicksort(v, s, p - 1);
    quicksort(v, p + 1, e);

}
//quick sort function to be used in binpacking problem.


int firstFit(vector<int> wt,  int capacity)
{
    int n=wt.size()-1;
	// Initialize result (Count of bins)
	int res = 1;

	// Create an array to store remaining space in bins
	// there can be at most n bins
	vector<int> bin_rem(n);

	// Place items one by one
	for (int i = 0; i < n; i++) {
		// Find the first bin that can accommodate
		// weight[i]
		int j;
		for (j = 0; j < res; j++) {
			if (bin_rem[j] >= wt[i]) {
				bin_rem[j] = bin_rem[j] - wt[i];
			
				break;
			}
		}

		// If no bin could accommodate weight[i]
		if (j == res) {
			bin_rem[res] = capacity - wt[i];
			res++;
		}
	
	}
	return res;
}

// Returns number of deliveries required using first fit


int firstFitDec(vector<int> wt,  int capacity)
{
	// First sort all weights in decreasing order
	quicksort(wt,0,wt.size()-1);

	// Now call first fit for sorted items
	return firstFit(wt, capacity);
}

//returns the numbers of deliveries required using first fit decreasing algorithm

#define V 10
//defining vertex as 9.

int minDistance(int dist[], bool sptSet[])
{
    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}
//function for finding out the minimum distance between sectors .To be used in dijkstra function.

int printSolution(int dist[], int n)
{

    int destination;

    cout << "Enter your destination";

    cin >> destination;

    printf("Smallest distance from your location\n");
    cout << "Total distance:  " << dist[destination]<<"kms"<<endl;

    if(dist[destination]<5)
    {
        cout<<"Your delivery will take 15 mins";
    }

    else if(dist[destination]>=5&&dist[destination]<10)
    {
        cout<<"Your delivery will take 30 mins";
    }

        else if(dist[destination]>=10&&dist[destination]<15)
        {
            cout<<"Your delivery will take 45 mins";

        }

            else if(dist[destination]>=15&&dist[destination]<20)
            {
                cout<<"Your delivery will take 1 hour";
            }

}
//function for printing the minimum diiference between the cities .To be used in the dijkstra function.

void dijkstra(int graph[V][V], int src)
{
    int dist[V]; //  dist[i] will hold the shortest distance
    // distance from src to i

    bool sptSet[V]; // sptSet[i] will be true if vertex i is included in shortest


    // Initialize the values
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

    // Distance of source from vertex  is  0
    dist[src] = 0;

    // Finding shortest path for all vertices
    for (int count = 0; count < V - 1; count++)
    {
        // Pick the minimum distance vertex from the set of vertices not

        int u = minDistance(dist, sptSet);

        // Mark the picked vertex as processed
        sptSet[u] = true;

        // Updating distance value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < V; v++)

            // Update dist[v] only if is not in sptSet, there is an edge from
            // u to v, and total weight of path from src to v through u iss maller than current value of dist[v]
            
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    // print the distance of source to destination
    printSolution(dist, V);

}

//dijkstra algo to find the shortest path between the source and destination

void DisplayOrder(struct PizzaTypes pizzaCart[100], struct PizzaCost costOnSize[12], vector<string> &itemNames, vector<int> &sidesCost);

//function definition  for displaying the order.Function implementation is done at the last. 

int main()
{

    vector<int> wt;
    //vector to hold the weights of the pizzas

    cout << "PIZZA ORDERING SYSTEM AND DELIVERY SYSTEM" << endl
         << endl;
    int i = 0, c = 1, j = 0, mainChoice, cost[24] = {99, 195, 395, 155, 295, 445, 155, 295, 445, 195, 365, 545, 155, 295, 445, 225, 425, 635, 235, 455, 685, 235, 455, 685}, totalCost = 0, a[10];
    char name[20];
    vector<string> itemNames = {

        "Margherita(Veg)",
        "Spicy Triple Tango(Veg)",
        "Double Cheese Margherita(Veg)",
        "Farm House(Veg)",
        "Cheese and Barbeque Chicken(Non Veg)",
        "Chicken Fiesta(Non Veg)",
        "Chicken Mexican(Non Veg)",
        "Chicken Golden Delight(Non Veg)",
        "Zingy Parcel Veg",
        "Zingy Parcel Non Veg",
        "Taco Mexicana Veg",
        "Taco Mexicana Non Veg"
        
        };

    vector<int> sidesCost = {29, 35, 119, 129};
    int weight = 0;
    struct PizzaTypes pizzaCart[100];
    struct PizzaCost costOnSize[12];

    for (i = 0; i < 12; i++)
    {
        pizzaCart[i].smallQuantity = 0;
        pizzaCart[i].mediumQuantity = 0;
        pizzaCart[i].largeQuantity = 0;
        pizzaCart[i].freshPan = 0;
        pizzaCart[i].wheatThinCrust = 0;
        pizzaCart[i].cheeseBurst = 0;
        pizzaCart[i].others = 0;
    }

    i = 0;

    while (i < 24)
    {
        costOnSize[j].smallCost = cost[i++];
        costOnSize[j].mediumCost = cost[i++];
        costOnSize[j].largeCost = cost[i++];
        costOnSize[j].freshPanCost = 30;
        costOnSize[j].cheeseBurstCost = 95;
        costOnSize[j].wheatThinCrustCost = 40;
        j++;

    }

    do
    {

        if (c == 1)
        {
            cout << "Enter" << endl
                 << "- Veg Pizzas" << endl
                 << "- Chicken Pizzas" << endl
                 << "- Sides" << endl
                 << "- Exit" << endl;
            cin >> mainChoice;

            switch (mainChoice)
            {

            case 1:
            {
                int subChoice;

                cout << "Enter" << endl
                     << "- Margherita" << endl
                     << " - Spicy Triple Tango" << endl
                     << "- Double Cheese Margherita" << endl
                     << " - Farm House" << endl
                     << " - Exit" << endl;
                cin >> subChoice;

                if (subChoice != 5)
                {
                    int sizeChoice;
                    cout << "Enter" << endl
                         << " - Small" << endl
                         << " - Medium" << endl
                         << " - Large" << endl;
                    cin >> sizeChoice;

                    if (sizeChoice == 1)
                    {
                        pizzaCart[subChoice - 1].smallQuantity++;
                        wt.push_back(5);
                        weight += 5;
                    }

                    if (sizeChoice == 2)
                    {
                        pizzaCart[subChoice - 1].mediumQuantity++;
                        weight += 7;
                         wt.push_back(7);
                    }

                    if (sizeChoice == 3)
                    {
                        pizzaCart[subChoice - 1].largeQuantity++;
                        weight += 10;
                         wt.push_back(10);
                    }

                    cout << "Need Special Crusts" << endl
                         << " - Fresh Pan" << endl
                         << " - Cheese Burst" << endl
                         << " - Wheat thin Crust" << endl
                         << " - No Need" << endl;
                    int extraCrust;
                    cin >> extraCrust;

                    if (extraCrust == 1)
                        pizzaCart[subChoice - 1].freshPan++;

                    else if (extraCrust == 2)
                        pizzaCart[subChoice - 1].cheeseBurst++;

                    else if (extraCrust == 3)
                        pizzaCart[subChoice - 1].wheatThinCrust++;

                    if (subChoice != 5)
                        cout << "Pizza Added to Cart Successfully" << endl;
                }

                break;
            }

            case 2:
            {
                int subChoice;
                cout << "Enter" << endl
                     << " - Cheese and Barbeque Chicken" << endl
                     << " - Chicken Fiesta" << endl
                     << " - Chicken Mexican" << endl
                     << "- Chicken Golden Delight" << endl
                     << "- Exit" << endl;

                cin >> subChoice;

                if (subChoice != 5)
                {
                    int sizeChoice;
                    cout << "Enter" << endl
                         << " - Small" << endl
                         << " - Medium" << endl
                         << " - Large" << endl;
                    cin >> sizeChoice;

                    if (sizeChoice == 1)
                    {
                        pizzaCart[subChoice + 4 - 1].smallQuantity++;
                        weight += 5;
                        wt.push_back(5);
                    }

                    if (sizeChoice == 2)
                    {
                        pizzaCart[subChoice + 4 - 1].mediumQuantity++;
                        weight += 7;
                          wt.push_back(7);
                    }

                    if (sizeChoice == 3)
                    {
                        pizzaCart[subChoice + 4 - 1].largeQuantity++;
                        weight += 10;
                          wt.push_back(10);
                    }

                    cout << "Need Special Crusts" << endl
                         << "1 - Fresh Pan" << endl
                         << "2 - Cheese Burst" << endl
                         << " 3- Wheat thin Crust" << endl
                         << " 4- No Need" << endl;

                    int extraCrust;
                    cin >> extraCrust;
                    if (extraCrust == 1)
                        pizzaCart[subChoice - 1].freshPan++;

                    else if (extraCrust == 2)
                        pizzaCart[subChoice - 1].cheeseBurst++;

                    else if (extraCrust == 3)
                        pizzaCart[subChoice - 1].wheatThinCrust++;

                    if (subChoice != 5)
                        cout << "Pizza Added to Cart Successfully" << endl;

                }

                break;

            }

            case 3:
            {
                int subChoice;
                cout << "Enter" << endl
                     << "1- Zingy Parcel Veg" << endl
                     << " 2- Zingy Parcel Non Veg" << endl
                     << "3- Taco Mexican Veg" << endl
                     << "4 - Taco Mexican Non Veg" << endl
                     << "5- Exit";

                cin >> subChoice;

                if (subChoice < 5 && subChoice > 0)
                    pizzaCart[subChoice + 8 - 1].others++;

                if (subChoice != 5)

                    cout << "Added to Cart Successfully" << endl;
                break;

            }

            default:

            {
                cout << "Invalid Choice" << endl;
                break;

            }

            }

        }

        if (c == 2)
        {
            int id, quantityPizza, quantityCrust, quantity, wrongIdFlag = 1;
            cout << "Enter Id to change Quantity" << endl;
            cin >> id;

            if (id >= 0 && id <= 11)
            {

                if (id >= 0 && id <= 7)

                {
                    if (pizzaCart[i].smallQuantity > 0 || pizzaCart[i].mediumQuantity > 0 || pizzaCart[i].largeQuantity || pizzaCart[i].others > 0 || pizzaCart[i].freshPan > 0 || pizzaCart[i].cheeseBurst || pizzaCart[i].wheatThinCrust > 0)
                    {
                        cout << "Enter" << endl
                             << "1 - To Change Small Pizza Quantity" << endl
                             << "2 -Change Quantity for Medium Pizza" << endl
                             << "3 -Change Quantity for Large Pizza" << endl
                             << "4 -Change Quantity for Crust" << endl
                             << "5 - Exit" << endl;
                        cin >> quantityPizza;
                        cout << "Enter quantity to change and to delete Enter 0";
                        cin >> quantity;

                        if (quantity >= 0)
                        {
                            if (quantityPizza == 1)
                                pizzaCart[id].smallQuantity = quantity;

                            if (quantityPizza == 2)
                                pizzaCart[id].mediumQuantity = quantity;

                            if (quantityPizza == 3)
                                pizzaCart[id].largeQuantity = quantity;

                            if (quantityPizza == 4)
                            {
                                cout << "Enter" << endl
                                     << "1 - To Change Fresh Pan" << endl
                                     << "2 - Cheese Burst" << endl
                                     << "3 - Wheat Thin Crust" << endl
                                     << "4 - Exit" << endl;

                                cin >> quantityCrust;
                                if (quantityCrust == 1)
                                    pizzaCart[id].freshPan = quantity;

                                if (quantityCrust == 2)
                                    pizzaCart[id].cheeseBurst = quantity;

                                if (quantityCrust == 3)
                                    pizzaCart[id].wheatThinCrust = quantity;

                            }

                        }
                        else
                        {
                            cout << "Enter Quantity greater than or equal to zero";
                        }
                    }

                    else
                    {
                        cout << "Id Not Found";
                        wrongIdFlag = 0;

                    }
                }

                else

                {
                    cout << "Enter" << endl
                         << "1 - To Change Quantity of Zingy Parcel(Veg)" << endl
                         << "2 - To Change Quantity of Zingy Parcel(Non Veg)" << endl
                         << "3 - To Change Quantity of Taco Mexicana(Veg)" << endl
                         << "4 - To Change Quantity of Taco Mexicana(Non Veg)" << endl
                         << "5 - To Change Quantity of  - Exit"<<endl
                         << endl;

                    cin >> quantityPizza;

                    if (quantityPizza >= 1 && quantityPizza <= 4)
                    {
                        cout << "Enter quantity" << endl;
                        cin >> quantity;
                        pizzaCart[id].others = quantity;

                    }

                }

                if (wrongIdFlag == 1)
                {
                    cout << "Quantity Changed Successfully" << endl
                         << "Rearranged Order is" << endl;
                    DisplayOrder(pizzaCart, costOnSize, itemNames, sidesCost);

                }

            }

            else
            {
                cout << "Please Enter Valid Id" << endl;
            }

        }

        if (c == 4)

        {
            int id;
            cout << "Enter Id to delete from Cart" << endl;
            cin >> id;
            pizzaCart[id].smallQuantity = 0;
            pizzaCart[id].mediumQuantity = 0;
            pizzaCart[id].largeQuantity = 0;
            pizzaCart[id].others = 0;
            pizzaCart[id].freshPan = 0;
            pizzaCart[id].cheeseBurst = 0;
            pizzaCart[id].wheatThinCrust = 0;
            weight = 0;
            cout << "Item Deleted Successfully\nRearranged Order is" << endl;
            DisplayOrder(pizzaCart, costOnSize, itemNames, sidesCost);
        }

        if (c == 3)
        {
            DisplayOrder(pizzaCart, costOnSize, itemNames, sidesCost);
        }

        cout << "Enter" << endl
             << "1 - Add Item" << endl
             << "2 - Change Quantity" << endl
             << "3 - View Cart" << endl
             << "4 - Delete from Cart" << endl
             << " Else any number to Calculate Cost" << endl;
        cin >> c;

    } 

    while (c == 1 || c == 2 || c == 3 || c == 4);

    

      // matrix representation of sectors

    int graph[V][V] = {{0, 4, 0, 0, 0, 0, 0, 8, 0,1},
                       {4, 0, 8, 0, 0, 0, 0, 11, 0,3},
                       {0, 8, 0, 7, 0, 4, 0, 0, 2,4},
                       {0, 0, 7, 0, 9, 14, 0, 0, 0,2},
                       {0, 0, 0, 9, 0, 10, 0, 0, 0,10},
                       {0, 0, 4, 14, 10, 0, 2, 0, 0,6},
                       {0, 0, 0, 0, 0, 2, 0, 1, 6,7},
                       {8, 11, 0, 0, 0, 0, 1, 0, 7,4},
                       {0, 0, 2, 0, 0, 0, 6, 7, 0,12},
                       {0,5,4,0,3,7,8,2,0,11    }        };

    
    vector<pair<int, string>> dest = {{0, "sector 16"}, {1, "sector 6"}, {2, "sector 62"}, {3, "sector 60"}, {4, "sector 67"}, {5, "sector 90"}, {6, "sector 96"}, {7, "sector 116"}, {8, "sector 126"}, {9,"sector 118"}};

    //displaying locations

    cout<<endl<<"NAMES OF THE LOCATIONS WHERE HOME DELIVERY IS AVAILABLE: "<<endl;

    for (auto it : dest)
    {
        cout << it.first << "     " << it.second << endl;
    }

    dijkstra(graph, 0);

    	int capacity = 15;
        cout<<endl;

	cout << "Final Order :" << endl;

    DisplayOrder(pizzaCart, costOnSize, itemNames, sidesCost);
     
	if((firstFitDec(wt,capacity)==1))
	{
		cout<<endl<<"Your order wiil be delivered as soon as possible"<<endl<<endl;

	}

	 if(firstFitDec(wt, capacity)==2)
     {
         cout<<endl<<"The delivery of Your order will take place in 2 times.Sorry for inconvenience."<<endl<<endl;

     }
      if(firstFitDec(wt,capacity)==3)
     {
         cout<<endl<<"The delivery of you order will take place in 3 times.Sorry for inconvenience."<<endl<<endl;

     }

    if(firstFitDec(wt,capacity)==4)
     {
         cout<<endl<<"The delivery of your order will take place in 4 times.Sorry for inconvenience."<<endl<<endl;


     }
	 if(firstFit(wt,capacity)>4) {

		 cout<<endl<<"Your order was cancelled beacue it was too large.Please order less quantity of food.Sorry for inconvenience"<<endl<<endl;

	 }



    cout << "Thanks for Shopping with us !!!!" << endl;

    return 0;

}

//main function


void DisplayOrder(struct PizzaTypes pizzaCart[100], struct PizzaCost costOnSize[12], vector<string> &itemNames, vector<int> &sidesCost)
{
    int totalCost = 0, i;

    cout << "---------------------List in Cart-------------------------" << endl;

    for (i = 0; i < 11; i++)
    {

        if (pizzaCart[i].smallQuantity > 0 || pizzaCart[i].mediumQuantity > 0 || pizzaCart[i].largeQuantity || pizzaCart[i].others > 0 || pizzaCart[i].freshPan > 0 || pizzaCart[i].cheeseBurst || pizzaCart[i].wheatThinCrust > 0)

        {

            if (i >= 0 && i <= 7)
            {

                cout << "Id : " << i << endl;
                cout << "Item Name : " << itemNames[i] << endl;
                if (pizzaCart[i].smallQuantity > 0)
                    cout << "Small Size Quantity: " << pizzaCart[i].smallQuantity << "-> Cost : " << costOnSize[i].smallCost * pizzaCart[i].smallQuantity << endl;

                if (pizzaCart[i].mediumQuantity > 0)
                    cout << "Medium Size Quantity: " << pizzaCart[i].mediumQuantity << " -> Cost : " << costOnSize[i].mediumCost * pizzaCart[i].mediumQuantity << endl;

                if (pizzaCart[i].largeQuantity > 0)
                    cout << "Large Size Quantity: " << pizzaCart[i].largeQuantity << " -> Cost : " << costOnSize[i].largeCost * pizzaCart[i].largeQuantity << endl;

                if (pizzaCart[i].freshPan > 0)
                    cout << "Fresh Pan Quantity: " << pizzaCart[i].freshPan << " -> Cost : " << costOnSize[i].freshPanCost * pizzaCart[i].freshPan << endl;

                if (pizzaCart[i].wheatThinCrust > 0)
                    cout << "Wheat Thin Crust Quantity: " << pizzaCart[i].wheatThinCrust << "-> Cost : " << costOnSize[i].wheatThinCrustCost * pizzaCart[i].wheatThinCrust << endl;

                if (pizzaCart[i].cheeseBurst > 0)
                    cout << "Cheese Burst Quantity: " << pizzaCart[i].cheeseBurst << " -> Cost : " << costOnSize[i].cheeseBurstCost * pizzaCart[i].cheeseBurst << endl;

                totalCost += pizzaCart[i].smallQuantity * costOnSize[i].smallCost;
                totalCost += pizzaCart[i].mediumQuantity * costOnSize[i].mediumCost;
                totalCost += pizzaCart[i].largeQuantity * costOnSize[i].largeCost;
                totalCost += pizzaCart[i].freshPan * costOnSize[i].freshPanCost;
                totalCost += pizzaCart[i].cheeseBurst * costOnSize[i].cheeseBurstCost;
                totalCost += pizzaCart[i].wheatThinCrust * costOnSize[i].wheatThinCrustCost;

            }

            else

            {
                cout << "Id : " << i << endl;
                cout << "Item Name : " << itemNames[i] << endl;
                cout << "Quantity : " << pizzaCart[i].others << endl;
                cout << "Cost : " << pizzaCart[i].others * sidesCost[i - 8] << endl;

                totalCost += (pizzaCart[i].others) * sidesCost[i - 8];
            }
            
        }

    }

    cout << "-------------------Total Cost : " << totalCost << endl;

  
}

//function for displaying orders

