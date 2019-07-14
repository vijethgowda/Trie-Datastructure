
// C++ implementation of search and insert 
// operations on Trie 
#include <bits/stdc++.h> 
#include <ctype.h>
using namespace std; 
  
const int ALPHABET_SIZE = 26; 
int count1=0;
  
// trie node 
struct TrieNode 
{ 
    struct TrieNode *children[ALPHABET_SIZE]; 
  
    // isEndOfWord is true if the node represents 
    // end of a word 
    bool isEndOfWord; 
}; 
  
// Returns new trie node (initialized to NULLs) 
struct TrieNode *getNode(void) 
{ 
    struct TrieNode *pNode =  new TrieNode; 
  
    pNode->isEndOfWord = false; 
  
    for (int i = 0; i < ALPHABET_SIZE; i++) 
        pNode->children[i] = NULL; 
  
    return pNode; 
} 
  
// If not present, inserts key into trie 
// If the key is prefix of trie node, just 
// marks leaf node 
void insert(struct TrieNode *root, string key) 
{ 
    struct TrieNode *pCrawl = root; 
  
    for (int i = 0; i < key.length(); i++) 
    { 
         count1++;
        int index = key[i] - 'a'; 
        if (!pCrawl->children[index]) 
            pCrawl->children[index] = getNode(); 
         
             //  cout<<count1<<". "<<pCrawl->children[index]<<endl;

        pCrawl = pCrawl->children[index]; 
    } 
  
    // mark last node as leaf 
    pCrawl->isEndOfWord = true; 
} 
  
// Returns true if key presents in trie, else 
// false 
bool search(struct TrieNode *root, string key) 
{ 
    struct TrieNode *pCrawl = root; 
  
    for (int i = 0; i < key.length(); i++) 
    { 
        int index = key[i] - 'a'; 
        if (!pCrawl->children[index]) 
            return false; 
  
        pCrawl = pCrawl->children[index]; 
    } 
  
    return (pCrawl != NULL && pCrawl->isEndOfWord); 
} 
 
bool isLeafNode(struct TrieNode* root) 
{ 
    return root->isEndOfWord != false; 
} 

void display(struct TrieNode *root, char str[], int level) 
{ 
    // If node is leaf node, it indiicates end 
    // of string, so a null charcter is added 
    // and string is displayed 
    if (isLeafNode(root))  
    { 
        str[level] = '\0'; 
        cout << str << endl; 
    } 
  
    int i; 
    for (i = 0; i < ALPHABET_SIZE; i++)  
    { 
        // if NON NULL child is found 
        // add parent key to str and 
        // call the display function recursively 
        // for child node 
        if (root->children[i])  
        { 
            str[level] = i + 'a'; 
            display(root->children[i], str, level + 1); 
        } 
    } 
} 

// Returns 0 if current node has a child 
// If all children are NULL, return 1. 
bool isEmpty(TrieNode* root) 
{ 
    for (int i = 0; i < ALPHABET_SIZE; i++) 
        if (root->children[i]) 
            return false; 
    return true; 
} 
  
// Recursive function to delete a key from given Trie 
TrieNode* remove(TrieNode* root, string key, int depth = 0) 
{ 
    // If tree is empty 
    if (!root) 
        return NULL; 
  
    // If last character of key is being processed 
    if (depth == key.size()) { 
  
        // This node is no more end of word after 
        // removal of given key 
        if (root->isEndOfWord) 
            root->isEndOfWord = false; 
  
        // If given is not prefix of any other word 
        if (isEmpty(root)) { 
            delete (root); 
            root = NULL; 
        } 
  
        return root; 
    } 
  
    // If not last character, recur for the child 
    // obtained using ASCII value 
    int index = key[depth] - 'a'; 
    root->children[index] =  
          remove(root->children[index], key, depth + 1); 
  
    // If root does not have any child (its only child got  
    // deleted), and it is not end of another word. 
    if (isEmpty(root) && root->isEndOfWord == false) { 
        delete (root); 
        root = NULL; 
    } 
  
    return root; 
} 

  
// Recursive function to print auto-suggestions for given 
// node. 
void suggestionsRec(struct TrieNode* root, string currPrefix) 
{ 
    // found a string in Trie with the given prefix 
    if (root->isEndOfWord) 
    { 
        cout << currPrefix; 
        cout << endl; 
    } 
  
    // All children struct node pointers are NULL 
    if (isEmpty(root)) 
        return; 
  
    for (int i = 0; i < ALPHABET_SIZE; i++) 
    { 
        if (root->children[i]) 
        { 
            // append current character to currPrefix string 
            currPrefix.push_back(97 + i); 
  
            // recur over the rest 
            suggestionsRec(root->children[i], currPrefix);
            currPrefix.pop_back(); 
        } 
    } 
} 
  
// print suggestions for given query prefix. 
int printAutoSuggestions(TrieNode* root, const string query) 
{ 
    struct TrieNode* pCrawl = root; 
  
    // Check if prefix is present and find the 
    // the node (of last level) with last character 
    // of given string. 
    int level; 
    int n = query.length(); 
    for (level = 0; level < n; level++) 
    { 
        int index = toascii(query[level]); 
            index-=97;
        // no string in the Trie has this prefix 
        if (!pCrawl->children[index]) 
            return 0; 
        
         //cout<<"xx";
   
        pCrawl = pCrawl->children[index]; 
    } 
  
    // If prefix is present as a word. 
    bool isWord = (pCrawl->isEndOfWord == true); 
  
    // If prefix is last node of tree (has no 
    // children) 
    bool isLast = isEmpty(pCrawl); 
  
    // If prefix is present as a word, but 
    // there is no subtree below the last 
    // matching node. 
    if (isWord && isLast) 
    { 
        cout << query << endl; 
        return -1; 
    } 
  
    // If there are are nodes below last 
    // matching character. 
    if (!isLast) 
    { 
        string prefix = query; 
        suggestionsRec(pCrawl, prefix); 
        return 1; 
    } 
} 
 
// Driver 
int main() 
{ 
    // Input keys (use only 'a' through 'z' 
    // and lower case) 
    string keys[] = {"the", "a", "there", 
                    "answer", "any", "by", 
                     "bye", "their","heroplane","hero" }; 
    int n = sizeof(keys)/sizeof(keys[0]); 
    int level = 0; 
    char str[20]; 
    struct TrieNode *root = getNode(); 
  
    // Construct trie 
    for (int i = 0; i < n; i++) 
     	 insert(root, keys[i]); 
    insert(root, "hello"); 
    insert(root, "dog"); 
    insert(root, "hell"); 
    insert(root, "cat"); 
    insert(root, "a"); 
    insert(root, "hel"); 
    insert(root, "help"); 
    insert(root, "helps"); 
    insert(root, "helping"); 
    
    // Search for different keys 
cout << "Content of Trie: " << endl; 
    display(root, str, level);

cout<<"-----------search----------------\n";
cout<<"searching for \"the\"";
    search(root, "the")? cout << " Found\n" : 
                         cout << " Not Found\n"; 
cout<<"searching for \"these\"";
    search(root, "these")? cout << "Found\n" : 
                         cout << "Not Found\n";

 
cout << "Content of Trie Before Delete: " << endl; 
    display(root, str, level); 
    
cout<<"-------------remove---------------\n";  
cout<<"Remove \"Heroplane\" "; 
   remove(root, "heroplane"); 
   search(root, "hero") ? cout << " Removed\n" : cout << " Not Found\n"; 
    // Displaying content of Trie 
cout << "Content of Trie After Delete: " << endl; 
   display(root, str, level); 
    
cout<<"----------autosuggestions----------\n";
  //printautosuggestions
cout<<"Enter the Word\n";
char a1[20];
cin>>a1;
int comp = printAutoSuggestions(root, a1); 
  
    if (comp == -1) 
        cout << "No other strings found with this prefix\n"; 
  
    else if (comp == 0) 
        cout << "No string found with this prefix\n"; 
  
    
    return 0; 
} 

