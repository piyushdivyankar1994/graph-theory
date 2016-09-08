#include <iostream>
#include <list>
#include <vector>
#include <iterator>

using namespace std;

/**
 * @class edge Used to represent one edge.
 */
class edge {
    private:
    int destinationVertex;     /*!< ::vertex.id of destination vertex in graph */
    public:
    /**
     * Counstructor for edge.
     */
    edge (int ver) : destinationVertex(ver) {
    }
    friend std::ostream& operator<<(std::ostream& a, edge const& e) {
            return a << e.destinationVertex;
    }
    /** @return value of ::destinationVertex */
    int getDestinationVertex() {
            return destinationVertex;
    }

    ~edge();
};

class graph;

/**
 * @class vertex
 * @brief Container for a vertex in a graph.
 * @details This container contains an id that refers to the number of the
 *          vertex. It also contains list of destinations, i.e the vertices
 *          connected to the vertex.
 */
class vertex {
    friend class graph;
    /** id of the vertex */
    int id;
    /** list of destinations */
    std::list<edge> list;

    public:
    /**
     * Counstructor that creates an new empty vertex.
     */
    vertex(int id) : id(id)
    {
    }
    /**
     * @brief Overloading for << operator.
     * @details friend function that overloads the << operator for vertex
     *          class and defines a printing behaviour.
     */
    friend std::ostream& operator<<(std::ostream& s, vertex const& v) {
            s << v.id << "->";
            std::copy(v.list.begin(), v.list.end(), std::ostream_iterator<edge>(s, ","));
            return s;
    }
    /**
     * Linear search for a in list of edges of the vertex.
     * @param  a value to search
     * @return   true if element matches, else false
     */
    bool find(int a) {
            for(std::list<edge>::iterator it = list.begin(); it != list.end(); ++it)
            {
                    if((*it).getDestinationVertex() == a)
                            return true;
            }
            return false;
    }
    /**
     * Returns degree of a vertex.
     * @return number of edges in vertex
     */
    int deg() {
            return list.size();
    }

    void removeEdge(const int id) {
        int k = find(id);
        list.remove_if();
    }
};

/**
 * @class graph
 * @brief Stores a graph as an adjacency list
 * @details A vector of vertexes is used to store vertices and their edges.
 */
class graph {
    private:
    /** List of vertices */
    std::vector<vertex> vertexes;
    /** @brief keeps the id of last unallocated vertex.
     *  @details In graph operations the vertex are numbered as [0,1,2 ... n-1]
     *           for a graph with n vertices. The next value in that case must
     *           be kept next = n;
     */
    int next;
    public:
    /** Counstructor to initialize a empty graph */
    graph() : next(0)
    {
    }
    /**
     * Adds new node to the graph that has certain edges.
     * @param edges vector containing edges of the vertex that needs to be added
     */
    void addNode(std::vector<int> const & edges) {
            vertexes.push_back(vertex(next));
            for (size_t i = 0; i < edges.size(); i++) {
                    vertexes[edges[i]].list.push_back(next);
                    vertexes[next].list.push_back(edges[i]);
            }
            next++;
    }

    /**
     * Operator overloading for <<
     */
    friend std::ostream& operator<<(std::ostream& s, graph const& g) {
            std::copy(g.vertexes.begin(), g.vertexes.end(), std::ostream_iterator<vertex>(s, "\n"));
            return s;
    }

    /**
     * Constructor for making an object with k vertices and no edges.
     */
    graph(int no_of_edges) {
            next = 0;
            for (size_t i = 0; i < no_of_edges; i++) {
                    vertexes.push_back(vertex(i));
            }
            next = no_of_edges;
    }

    /**
     * Insert new edges in a graph at given vertex
     * @param id    Insert in this vertex
     * @param edges add these edges
     */
    void addEdges(int id, std::vector<int> const & edges) {
            for (size_t i = 0; i < edges.size(); i++) {
                    vertexes[id].list.push_back(edges[i]);
                    vertexes[edges[i]].list.push_back(id);
            }
    }

    /**
     * Insert a single edge between first and second vertex
     * @param first  first vertex
     * @param second second vertex
     */
    void insertEgde(int first, int second) {
            if(first >= next) {
                    std::cout << "Invlid vertex, vertices form 0 to" << next - 1
                    << std::endl;
                    return;
            }
            else if (second >= next) {
                    std::cout << "Invalid edge destination vertex, vertices from 0 to"
                    << next - 1 << std::endl;
                    return;
            }
            if(first == second) {
                    vertexes[first].list.push_back(first);
            }
            else if( !vertexes[first].find(second)) {
                    vertexes[first].list.push_back(second);
                    vertexes[second].list.push_back(first);
            }
    }

    /** Overloading on operator >> */
    friend std::istream &operator>>(std::istream &input, graph& g) {
            int v, e;
            input >> v >> e;
            g.insertEgde(v, e);
            return input;
    }

    /**
     * Number of vertices in graph
     * @return Number of vertices
     */
    int V() {
            return next;
    }

    /**
     * Number of edges in graph
     * @return number of edges.
     */
    int E() {
            int i = 0;
            for(std::vector<vertex>::iterator it = vertexes.begin();
                it != vertexes.end();
                ++it)
            {
                    i += (*it).deg();
            }
            return i / 2;
    }
    /**
     * return degree of vertex V
     * @param  V
     * @return   degree of V
     */
    int degree(int V){
            if(V > next) {
                    std::cout << "Out of bounds" << std::endl;
                    return 0;
            }
            return vertexes[V].deg();
    }
    /**
     * Maximum degree among all vertices.
     * @return Value of maximum degree
     */
    int maximumDegree(){
            int max = 0;
            for(std::vector<vertex>::iterator it = vertexes.begin();
                it != vertexes.end();
                ++it)
            {
                    if((*it).deg() > max) max = (*it).deg();
            }
            return max;
    }
    /**
     * Average of degrees of all vertices
     * @return as it says
     */
    float averageDegree() {
            return 2 * (float)this->E() / (float)this->V();
    }

    /**
     * Finds number of self loops
     * @return as it says
     */
    int selfLoops() {
            int loops = 0;
            for(std::vector<vertex>::iterator it = vertexes.begin();
                it != vertexes.end();
                ++it)
            {
                    if((*it).find((*it).id))
                            loops++;
            }
            return loops;
    }
    /**
     * Removes vertex with number id
     * @details     Removing is considered the same as removing all the edges that
     *              contain that vertex. So after deleting a vertex printing the graph
     *              will show that vertex but it won't have any edges.
     * @param id    id of the vertex to delete.
     */
    void deleteVertex(int id) {
        for(std::list<edge>::iterator it = vertexes[id].list.begin();
            it != vertexes[id].list.begin();
            ++it)
        {
            int k = (*it).getDestinationVertex();
            vertexes[k].removeEdge(id);
        }
    }
};

int main(int argc, char const *argv[]) {

        graph g(4);
        int ver0[] = {3, 1};
        std::vector<int> v (ver0, ver0 + sizeof(ver0)/sizeof(ver0[0]));
/*    g.addNode(v);
    v.push_back(0);
    g.addNode(v);
    v.push_back(1);
    g.addNode(v);
    v[0]=2;
    g.addNode(v);
 */
        g.addEdges(0, v);
        std::cout << g << std::endl;
        std::cout << "graph\n" << g << std::endl;
        for (size_t i = 0; i < 3; i++) {
                std::cout << "Type pairs (v,e) to add egde in graph" << std::endl;
                std::cin >> g;
        }

        std::cout << "adjacency list\n" << g << std::endl;
        std::cout << "degree of 2\n" << g.degree(2) << std::endl;
        std::cout << "graph edges\n" << g.E() << std::endl;
        std::cout << "maximumDegree\n" << g.maximumDegree() << std::endl;
        std::cout << "Average degree\n" << g.averageDegree() << std::endl;
        std::cout << "Self Loops\n" << g.selfLoops() << std::endl;
        return 0;
}
