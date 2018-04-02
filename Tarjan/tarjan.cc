#include <iostream>
#include <stack>
#include <queue>
#include <Graph.h>





void Graph::Tarjan_SCC(){
  
std::stack<Graph::Node> Q;
int time{0};

std::cout << "##########################################################" << std::endl;
for( unsigned int i=0; i<nodes.size(); i++ ){
  #ifdef DEBUG
  std::cout << "Graph::Tarjan_SCC scanning node " << nodes[i].get_name() << std::endl;
  #endif
  if( nodes[i].get_col() == color::white ){
    #ifdef DEBUG
       	std::cout << "color is white " << std::endl;
    #endif
       	time = nodes[i].Tarjan_SCC(time, Q, SCCs);
  }
}

 for( unsigned int scc=0; scc<SCCs.size(); scc++ ){
   std::cout << "SCC: " << scc << std::endl;
   for( unsigned int c=0; c<SCCs[scc].size(); c++){
     std::cout << SCCs[scc][c] << " ";
   }
   std::cout << std::endl;
 }

std::cout << "##########################################################" << std::endl;
 
} // Tarjan_SCCint








int Graph::Node::Tarjan_SCC(int time, std::stack<Graph::Node>& Q, std::vector<std::vector<int>>& SCCs){
  #ifdef DEBUG
    std::cout << "Node::Tarjan on Node " << this->name << std::endl;
  #endif
  this->print_all();
  this->set_disc(time);
  if( this->get_col() == color::white ){
    this->set_ll(time);
    }
  time++;
  // if( this->get_col() == color::white )
  #ifdef DEBUG
  std::cout << "discovery time: " << this->get_disc() << std::endl;
  std::cout << "low link: " << this->get_ll() << std::endl;
  #endif
  Q.push(*this);
  this->set_col(color::grey);
  

  
  for( Graph::Node* w : adj){
    if( w->get_col() == color::white ){
      time = w->Tarjan_SCC(time, Q, SCCs);
      this->set_ll( this->get_ll() < w->get_ll() ? this->get_ll() : w->get_ll() );
      #ifdef DEBUG
    std::cout << "Node::Tarjan on Node " << this->get_name();
    std::cout << " set lowlink to " << this->get_ll() << std::endl;
      #endif
    }
    else{
      if( w->get_col() == color::grey){
        this->set_ll( this->get_ll() < w->get_ll() ? this->get_ll() : w->get_ll() );
      #ifdef DEBUG
    std::cout << "#Node::Tarjan on Node " << this->get_name();
    std::cout << " set lowlink to " << this->get_ll() << std::endl;
      #endif
      }
    }
  }  


  
  this->set_col(color::black);
  if( this->get_ll() == this->discovery_time ){
    #ifdef DEBUG
    std::cout << "Node::Tarjan on Node " << this->get_name();
    std::cout << " lowlink = discovery time " << this->get_disc() << this->get_ll() << std::endl;
    #endif
    std::vector<int> temp;
    while( Q.top() != *this && !Q.empty() ){
      #ifdef DEBUG
        std::cout << "Node::Tarjan on Node " << this->get_name();
        std::cout << " pushing " << Q.top().get_name() << std::endl;
      #endif
      temp.push_back( Q.top().get_name() );
      Q.pop();
    }
    
      #ifdef DEBUG
        std::cout << "Node::Tarjan on Node " << this->get_name();
        std::cout << " pushing " << Q.top().get_name() << std::endl;
      #endif
	temp.push_back( Q.top().get_name() );
    Q.pop();
    SCCs.push_back(temp);
  }

  return time;
} // Node::Tarjan_SCCint
