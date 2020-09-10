#include <boost/config.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/johnson_all_pairs_shortest.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include <iostream> // cerr
#include <limits>
#include <random>   // mt19937_64, uniform_x_distribution
#include <vector>

#include "CLI/ProgressBar.hpp"
#include "johnson.hpp"

using namespace johnson;

graph_t *johnson::johnson_init(std::vector<dist_t> adj_matrix) {
  const dist_t max = std::numeric_limits<dist_t>::max();
  size_t E = 0;
  for (size_t i = 0; i < adj_matrix.size(); i++) {
    if (adj_matrix[i] < max) {
      E++;
    }
  }

  unsigned int n = boost::numeric_cast<unsigned int>(sqrt((double) adj_matrix.size()));

  Edge *edge_array = new Edge[E];
  dist_t *weights = new dist_t[E];
  size_t ei = 0;

  for (unsigned int i = 0; i < n; i++) {
    for (unsigned int j = 0; j < n; j++) {
      if (adj_matrix[((size_t) i) * ((size_t) n) + ((size_t) j)] != 0 && adj_matrix[((size_t) i) * ((size_t) n) + ((size_t) j)] != max) {
        edge_array[ei] = Edge(i, j);
        weights[ei] = adj_matrix[((size_t) i) * ((size_t) n) + ((size_t) j)];
        ei++;
      }
    }
  }

  graph_t *gr = new graph_t;
  gr->V = n;
  gr->E = E;
  gr->edge_array = edge_array;
  gr->weights = weights;

  return gr;
}

graph_t *johnson::johnson_init2(const unsigned int n, const double p,
                                const unsigned long seed) {
  static std::uniform_real_distribution<double> flip(0, 1);
  static std::uniform_int_distribution<unsigned int> choose_weight(1, 100);

  const dist_t max = std::numeric_limits<dist_t>::max();

  std::mt19937_64 rand_engine(seed);

  dist_t *adj_matrix = new dist_t[((size_t) n) * ((size_t) n)];

  size_t E = 0;
  for (unsigned int i = 0; i < n; i++) {
    for (unsigned int j = 0; j < n; j++) {
      if (i == j) {
        adj_matrix[((size_t) i) * ((size_t) n) + ((size_t) j)] = 0;
      } else if (flip(rand_engine) < p) {
        adj_matrix[((size_t) i) * ((size_t) n) + ((size_t) j)] = choose_weight(rand_engine);
        E++;
      } else {
        adj_matrix[((size_t) i) * ((size_t) n) + ((size_t) j)] = max;
      }
    }
  }
  Edge *edge_array = new Edge[E];
  dist_t *weights = new dist_t[E];
  size_t ei = 0;
  for (unsigned int i = 0; i < n; i++) {
    for (unsigned int j = 0; j < n; j++) {
      if (adj_matrix[((size_t) i) * ((size_t) n) + ((size_t) j)] != 0 && adj_matrix[((size_t) i) * ((size_t) n) + ((size_t) j)] != max) {
        edge_array[ei] = Edge(i, j);
        weights[ei] = adj_matrix[((size_t) i) * ((size_t) n) + ((size_t) j)];
        ei++;
      }
    }
  }

  delete[] adj_matrix;

  graph_t *gr = new graph_t;
  gr->V = n;
  gr->E = E;
  gr->edge_array = edge_array;
  gr->weights = weights;

  return gr;
}

void johnson::free_graph(graph_t *g) {
  delete[] g->edge_array;
  delete[] g->weights;
  delete g;
}

inline bool bellman_ford(graph_t *gr, dist_t *dist, size_t src) {
  auto V = gr->V;
  auto E = gr->E;
  Edge *edges = gr->edge_array;
  dist_t *weights = gr->weights;

  const dist_t max = std::numeric_limits<dist_t>::max();

#pragma omp parallel for
  for (long i = 0; i < V; i++) {
    dist[i] = max;
  }
  dist[src] = 0;

  for (size_t i = 1; i <= V - 1; i++) {

#pragma omp parallel for
    for (size_t j = 0; j < E; j++) {
      unsigned int u = std::get<0>(edges[j]);
      unsigned int v = std::get<1>(edges[j]);
      dist_t new_dist = weights[j] + dist[u];
      if (dist[u] != max && new_dist < dist[v])
        dist[v] = new_dist;
    }
  }

  bool no_neg_cycle = true;

#pragma omp parallel for
  for (size_t i = 0; i < E; i++) {
    unsigned int u = std::get<0>(edges[i]);
    unsigned int v = std::get<1>(edges[i]);
    dist_t weight = weights[i];
    if (dist[u] != max && dist[u] + weight < dist[v])
      no_neg_cycle = false;
  }
  return no_neg_cycle;
}

void johnson::johnson_parallel(graph_t *gr, dist_t *output) {

  size_t V = gr->V;
  const int V_uint = boost::numeric_cast<int>(V);

  // Make new graph for Bellman-Ford
  // First, a new node q is added to the graph, connected by zero-weight edges
  // to each of the other nodes.
  graph_t *bf_graph = new graph_t;
  bf_graph->V = V + 1;
  bf_graph->E = gr->E + V;
  bf_graph->edge_array = new Edge[bf_graph->E];
  bf_graph->weights = new dist_t[bf_graph->E];

  std::memcpy(bf_graph->edge_array, gr->edge_array, gr->E * sizeof(Edge));
  std::memcpy(bf_graph->weights, gr->weights, gr->E * sizeof(dist_t));
  std::memset(&bf_graph->weights[gr->E], 0, V * sizeof(dist_t));

#pragma omp parallel for
  for (int e = 0; e < V_uint; e++) {
    bf_graph->edge_array[((size_t) e) + gr->E] = Edge(V_uint, e);
  }

  // Second, the Bellman–Ford algorithm is used, starting from the new vertex q,
  // to find for each vertex v the minimum weight h(v) of a path from q to v. If
  // this step detects a negative cycle, the algorithm is terminated.
  // TODO Can run parallel version?
  dist_t *h = new dist_t[bf_graph->V];
  bool r = bellman_ford(bf_graph, h, V);
  if (!r) {
    std::cerr << "\nNegative Cycles Detected! Terminating Early\n";
    exit(1);
  }
  // Next the edges of the original graph are reweighted using the values
  // computed by the Bellman–Ford algorithm: an edge from u to v, having length
  // w(u,v), is given the new length w(u,v) + h(u) − h(v).
  size_t ec = gr->E;

#pragma omp parallel for
  for (long e = 0; e < ec; e++) {
    unsigned int u = std::get<0>(gr->edge_array[e]);
    unsigned int v = std::get<1>(gr->edge_array[e]);
    gr->weights[e] = gr->weights[e] + h[u] - h[v];
  }

  Graph G(gr->edge_array, gr->edge_array + gr->E, gr->weights, V);

  ProgressBar progress(V);

#pragma omp parallel for schedule(dynamic)
  for (int s = 0; s < V_uint; s++) {
    std::vector<dist_t> d(num_vertices(G));
    dijkstra_shortest_paths(G, s, boost::distance_map(&d[0]));
    for (size_t v = 0; v < V; v++) {
      output[((size_t) s) * V + v] = d[v] + h[v] - h[s];
    }
    ++progress;
  }

  delete[] h;
  free_graph(bf_graph);
}
