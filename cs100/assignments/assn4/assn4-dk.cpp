// David Klein
// CS 100
// Assignment 4
// Due: Oct 31, 2011

#include <iostream>
#include <string.h>
#include <vector.h>
#include <map.h>

using namespace std;

#define each(I) \
	for( __typeof__ ((I).begin()) it=(I).begin(); it!=(I).end(); ++it)

template< typename Item >
class priority_queue
{
	map<Item, float> index;
	vector<Item> vec;
	map<Item, float> priority;
	int last() { return vec.size()-1; }
	bool exists( int i ) { return i <= last(); }
	//int first() { return 0; }
	int parent( int i ) { return (i-1)/2; }
	int left( int i ) { return 2*i+1; }
	int right( int i ) { return 2*i+2; }
	bool is_leaf( int i ) { return !exists( left() ); }
	bool preceeds( int i, int j )
	{
		return exists(i) && priority[vec[i]] <= priority[vec[j]];
	}
	int sswap( int i, int j )						// swap our vector elements
	{
		swap( vec[i], vec[j] );
		swap( index[vec[i]], index[vec[j]] );
		return 0;
	}
	void percolate_up( )
	{
		int position = 0;							// while our next position is > then our
		while( position < last() && !vec.empty() )	// current then we swap. and we do this all up
		{
			if( preceeds( position+1, position ) )
				sswap( position, position+1 );
			if( !preceeds( position+1, position ) )
				break;
		}
	}
	void percolate_down( )
	{
		int i = last() - 1;
		int j = last();
		while( preceeds( i--, j-- )	)					// while our position is < then our
		{											// current then we swap. and we do this downward
			sswap( i, j );
		}
	}
public:
	map<Item, bool> enqueued;						// determines if the the word is already in our list
	bool empty() { return vec.empty(); }
	Item front( ) { return vec.front(); }
	void pop()
	{
		if( vec.empty() )
		{
			cout << "Cannot pop off empty queue" << endl;
			return;
		}
		enqueued[vec.front()] = false;	// we make sure to de-enqueue the front of the heap frst
		vec.front() = vec.back();		// swap the back for the front
		vec.pop_back();					// then pop off the back
	//	percolate_up();					// then percolate the new front node up the list
	}
	int push( Item w, float prio )
	{
		enqueued[w] = true;				// adding new element, we enqueue it into the list
		priority[w] = prio;				// set its priority
		vec.push_back( w );				// and push it onto the back
		if( vec.size() > 1 )
//			percolate_down();			// then we percolate down the list till its in its
		return 1;						// priority spot
	}
	void print()
	{
		for( unsigned int i = 0; i < vec.size(); ++i )
			cout << vec[i] << endl;
		cout << "one push" << endl;
	}
};

template< typename Node >
map<Node, Node> dijkstra( map< Node, map<Node, float> > d, Node source )
{
	map<Node, Node> parent;				// tree to be returned
	map<Node, bool> in_tree;
	map<Node, float> dist;				// per node distance to source

	priority_queue<Node> worklist;		// our worklist which stores our heap
	dist[source] = 0;
	worklist.push(source, 0);			// set our start word (root) as first and set its
										// distance = 0
	while( !worklist.empty() )			// while our heap is not empty...
	{
		string closest = worklist.front();	// temp value that stores the first element in our heap
		worklist.pop();						// then we remove it to bring up the next element in the queue
		in_tree[closest] = true;			// since we popped it off we can now tell our tree that
											// it contains this element
		each( d[closest] )					// iterate through each of the neighbors
		{
			Node neighbor = (*it).first;
			if( in_tree[neighbor] )
				continue;
			float x = dist[closest] + d[closest][neighbor];	// distance from our previous node to the root
			if( dist[neighbor] == 0 || dist[neighbor] >= x )
			{
				if( worklist.push(neighbor, x) ) // push our neighbor and its priority onto the heap
				dist[neighbor] = x;
			}
			parent[neighbor] = closest;
		}
	}
	return parent;
}

int main( int argc, char* argv[] )
{
	if( argc != 3 )
	{
		cerr << argv[0] << " usage: start end < dictionary\n";
		exit(-1);
	}
	map< string, bool > in_dict;
	map< string, map<string, float> > d;				// map of maps
	for( string s; cin >> s; )
	{
		in_dict[s] = true;
		for( unsigned int i = 0; i!= s.size(); ++i )	// this builds our adjacency list
		{
			for( char c = 'a'; c != 'z'; ++c )
			{
				string w = s;
				w[i] = c;
				if( in_dict[w] )						// if the new word (different by one
				{										// character is in the dictionary then
					d[w][s] = d[s][w] = 1;				// we add it to the list and set the
				}										// distance between both to 1
			}
		}
		d[s][s] = 0;
	}

	string start_word = argv[1];						// pass in start word from console
	map<string, string> parent = dijkstra( d, start_word ); // pass in our adjacency list and end
	for( string s = argv[2]; s != ""; s = parent[s] )		// word from console
	{
		cout << s << endl;								// print our shortest path to the word
		if( s == start_word )
			exit(0);
	}
	exit(1);
	return 0;
}

