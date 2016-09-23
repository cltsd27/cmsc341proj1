#ifndef _LLAMA_CPP_
#define _LLAMA_CPP_

#include <sstream>
#include "Llama.h"


template <class T, int LN_SIZE>
Llama<T, LN_SIZE>::Llama() {
  m_initialNode = new LlamaNode<T, LN_SIZE>;
  m_lastNode = m_initialNode;
  m_numNodes = 1;
  m_numData = 0;
  m_hasExtraNode = false;
}

template <class T, int LN_SIZE>
void Llama<T, LN_SIZE>::push(const T& data){
  //is there more data than 1 node?
  if (m_numData > LN_SIZE - 1) {
    //if the m_numData is a multiple of LN_SIZE, create a new node
    if (m_numData % LN_SIZE == 0 && !m_hasExtraNode) {
      m_lastNode->m_next = new LlamaNode<T, LN_SIZE>;
      m_numNodes++;
      m_lastNode = m_lastNode->m_next;
      m_lastNode->arr[0] = data;
    }
    //extra node means that the new m_last node is the extra node
    else if (m_hasExtraNode) {
      m_lastNode = m_lastNode->m_next;
      m_lastNode->arr[m_numData - LN_SIZE * (m_numNodes - 1)] = data;
    }
    //otherwise add the data to the m_lastNode
    else {

      //the index needed is the m_number of data - the size of each node
      //* the m_number of nodes minus the current node
      m_lastNode->arr[m_numData - LN_SIZE * (m_numNodes - 1)] = data;
    }
  } else {
    m_lastNode->arr[m_numData] = data;
  }
  m_numData++;
}

template <class T, int LN_SIZE>
void Llama<T, LN_SIZE>::dump() {
  //Llama instance info
  cout << "***** Llama Stack Dump ******" << endl;
  cout << "LN_SIZE = " << LN_SIZE << endl;
  cout << "# of items in the stack = " << m_numData << endl;
  LlamaNode<T, LN_SIZE>::report();
  cout << endl;
  //stack info
  cout << "This stack " << (m_hasExtraNode ? "has " : "does not have ") << "an extra node" << endl;
  cout << endl << "Stack contents, top to bottom" << endl;
  std::string dashes = "----";
  std::string stackContents =  dashes + " ";
  std::stringstream ss;
  ss << m_initialNode;
  stackContents += ss.str();
  stackContents += " " + dashes + "\n";
  if(m_lastNode == m_initialNode) {
    std::string nodeContents = getNodeContents(m_initialNode, m_numData);
    stackContents += nodeContents;
  } else {
    std::string nodeContents = getNodeContents(m_initialNode, LN_SIZE);
    stackContents += nodeContents;
  }
  stackContents += dashes + " " + "bottom of stack " + dashes + "\n";
  LlamaNode<T, LN_SIZE> *node = m_initialNode;
  //grab info for each stack and put it on top of the last one
  //to create a 'descending stack' 
  for(int i = 0; i < m_numNodes-1; ++i){
    node = node->m_next;
    std::string curNodeInfo;
    curNodeInfo =  dashes + " ";
    std::stringstream curss;
    curss << node;
    curNodeInfo += curss.str();
    curNodeInfo += " " + dashes + "\n";
    if(node == m_lastNode) {
      std::string nodeContents = getNodeContents(node, m_numData - LN_SIZE*(m_numNodes - 1));
      curNodeInfo += nodeContents;
    } else {
      std::string nodeContents = getNodeContents(node, LN_SIZE);
      curNodeInfo += nodeContents;
    }
    stackContents = curNodeInfo + stackContents;
  }
  cout << stackContents;
}

template <class T, int LN_SIZE>
std::string Llama<T, LN_SIZE>::getNodeContents(LlamaNode<T, LN_SIZE> *node, int finalIndex) const {
  std::string nodeContents;
  for(int i = 0; i < finalIndex; ++i) {
    std::stringstream ss;
    ss << node->arr[i];
    nodeContents = ss.str() +"\n" + nodeContents;
  }
  return nodeContents;
}

template <class T, int LN_SIZE>
Llama<T, LN_SIZE>::~Llama(){
 
}

template <class T, int LN_SIZE>
int Llama<T, LN_SIZE>::size() {
  return m_numData;
}

#endif
