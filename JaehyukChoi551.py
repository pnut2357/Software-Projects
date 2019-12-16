################################################################################
# FILE: JaehyukChoi_HW4_CSE551.py
# AUTHOR: Jaehyuk Choi (1215326372)
# CONTACT INFO: jchoi154@asu.edu
#
# COURSE INFO
# EEE551 Fall 2019
# Homework4 12-01-2019 / Time: 1:30pm - 2:45pm TuTh
#
# DESCRIPTION
# The program computes and outputs the max-flow by using NetworkX for the given
# problem. Given the source, destination, and intermediate airports, the project
# requests to compute the capacity of a simplified model from source to destination
# on January 6, 2020, in a 24 hour time period ; Source as Los Angeles (LAX),
# Destination as New York (JFK), and intermediate airports are San Francisco (SFO),
# Phoenix (PHX), Seattle (SEA), Denver (DEN), Atlanta (ATL), Chicago (ORD), Boston
# (BOS), and Washington DC (IAD). The airlines of American Airlines (AA), Delta
# Airlines (DL), and United Airlines (UA). Based on a graph theory, each node was
# designed as each airport such as source node (LAX), sink node (JFK), and
# intermediate nodes (8 airports listed above). Each edge was constructed if
# augmenting path conditions and time constraint are met. Using Edmonds-Karp
# algorithm, the capacity of the network was computed as 5724 with its average
# time duration of the algorithm 0.277 seconds.
################################################################################

import pandas as pd
import numpy as np
import networkx as nx
import sys
import timeit
################################################################################
# The function extracts all the available paths from source to sink and returns
# the list of the edges. In the Edmonds-Karp algorithm, the only case that back-
# edges happen is when a shorter path shares the path used up with a longer path.
# In the case, augment the flow in the possible paths. If min cost flow of the
# shorter path is greater than the min cost flow of longer path, subtract the
# minimum value among the augmented flow.
#
# Inputs:
#    MultiG - multi directed graph function from NetworkX
#    shortest_path - the shortest path among the available paths
#    now - the present arrival time at intermediate nodes toward sink.
#    storage - stores the the flight in the order of earliest arrival time.
# Output:
#    MultiG, found_path, list_of_edges, storage
################################################################################
def check_avaiable_path (MultiG, shortest_path, now, storage):
    found_path = True         # to check if available paths are found.
    list_of_edges = []        # stores available edges
    for i in range(len(shortest_path)-1):
        found_available_path = True
        u = shortest_path[i]
        v = shortest_path[i+1]
        try:
            availableflights = MultiG[u][v]
            #print("POSSIBLE FLIGHT", availableflights)
            # items for possible combinations of flight paths.
            if u + v in storage:
                items = storage[u + v]
                #print("items", items)
            else:
                items = sorted(dict(availableflights),
                        key=lambda t: dict(availableflights)[t]['arr_time'],
                        reverse=False)
                storage[u + v] = items

        except:
            # no path from u to v
            found_available_path = False

        foundpath_u_v = False             # to check if there is path from u to v
        if found_available_path == True:  # if there is available path between u and v
            for j in range(len(availableflights)):
                info = availableflights[items[j]] # stores possible flights.
                # edge construction conditions.
                cond1 = (MultiG.nodes[v]['label']=='none')
                cond2 = (info['flow'] < info['cap'])
                cond3 = (now <= info['dep_time'])
                if cond1 and cond2 and cond3:
                    foundpath_u_v = True
                    # now is the present of arrival time at each node.
                    now = info['arr_time']
                    # at node v, label the flight's index.
                    MultiG.nodes[v]['label'] = info['flightidx']
                    # add the edge to list of edges.
                    list_of_edges.append(info)

            if foundpath_u_v == False: # no available path
                found_path = False
            else: # if there is an available path
                found_path = True
        if found_available_path == False:
            found_path = False
            print('NO flight available')
            sys.exit()

    return MultiG, found_path, list_of_edges, storage

################################################################################
# The function updates the min cost flow to the available edges if it meets the
# edge conditions (cond1: u visited but v not visited yet, cond2: f(e) < C(e),
# and cond3: e[‘arrival time’] <= e[‘departure time’]) and augment the total flow.
#
# Inputs:
#    MultiG - multi directed graph function from NetworkX
#    shortest_path - the shortest path among the available paths
#    list_of_edges - list of edge candiates
#    Total_flow - the flow to be augmented
# Output:
#    MultiG, Total_flow
################################################################################
def min_cost_flow_updater (MultiG, shortest_path, list_of_edges, Total_flow):
    cost_flow_list = np.full(len(list_of_edges),np.Inf,int) # storing cost flow list.

    for i in range(len(shortest_path)-1):
        u = shortest_path[i]      # for node u
        v = shortest_path[i+1]    # for node v
        e_u = list_of_edges[i]['u'] # for edge from u to v and its flight index.
        e_v = list_of_edges[i]['v']
        e_idx = list_of_edges[i]['flightidx']

        info = MultiG[e_u][e_v][e_idx]
        cost_flow_list[i] = info['cap'] - info['flow'] # computes the cost_flow for each edge.
    # choose the min cost flow among the cost flows at available paths.
    min_cost_flow = min(cost_flow_list)
    for i in range(len(shortest_path)-1):
        u = shortest_path[i]                # to assign the min cost flow value.
        v = shortest_path[i+1]
        e_u = list_of_edges[i]['u']
        e_v = list_of_edges[i]['v']
        e_idx = list_of_edges[i]['flightidx']

        info = MultiG[e_u][e_v][e_idx]
        MultiG[u][v][info['flightidx']]['flow'] += min_cost_flow

    Total_flow += min_cost_flow             # updates the Total_flow.

    return MultiG, Total_flow

################################################################################
# The function labels the arrival time for each possible path from source to sink,
# sort those paths by arrival time, and returns the list of paths with recorded
# arrival time.
#
# Inputs:
#    MultiG - multi directed graph function from NetworkX
#    list_of_paths - list of the paths from the data
# Output:
#    MultiG, path_of_recordednow, storage
################################################################################
def timesorting(MultiG, list_of_paths):
    storage = {}
    path_of_recordednow = pd.DataFrame(list_of_paths)

    timerecorder = []

    for path in list_of_paths:

        # resets the labels of existing nodes
        for city in MultiG.nodes:
            MultiG.nodes[city]['label'] = 'none'
        now = pd.to_datetime('12:00 AM').strftime('%H:%M')
        MultiG, found_path, list_of_edges, storage = check_avaiable_path(MultiG,path,now,storage)
        if found_path:
            timerecorder += [now]
        else:
            timerecorder += [np.nan]
    path_of_recordednow.insert(path_of_recordednow.shape[1],'recorded_arr_time',timerecorder)
    path_of_recordednow = path_of_recordednow.dropna('index')
    path_of_recordednow = path_of_recordednow.sort_values('recorded_arr_time', ascending=[True])
    return MultiG, path_of_recordednow, storage

################################################################################
# The function returns the non-empty list of the paths with incremented
# intermediate nodes.
#
# Inputs:
#    MultiG - multi directed graph function from NetworkX
#    CombinedG - graph for the combined all edges from multiple directed graph.
#    num_stops - number of intermediate nodes.
# Output:
#    MultiG, CombinedG, list_of_paths
################################################################################
def check_stops(MultiG, CombinedG, num_stops):
    nodelength = len(MultiG)        # finds the length of nodes
    # list of the paths from the data with intermediate nodes
    # depending on the number of intermediate nodes, it goes from shortest to
    # longest paths.
    list_of_paths = [path for path in nx.all_simple_paths(CombinedG,SOURCE,SINK,num_stops)]
    # finds the list of the paths until it finds the list is not empty
    for num_stops in range(2, nodelength-1):
        if len(list_of_paths) == 0:
            list_of_paths = [path for path in nx.all_simple_paths(CombinedG,SOURCE,SINK,num_stops)]

    return MultiG, CombinedG, list_of_paths

################################################################################
# Main
################################################################################
#===============================================================================
# INPUT:
# FLIGHT_DATA.csv
# MultiDiGraph()
# add_edges()
# SOURCE: Origin of LAX inputted as ‘LAX’
# SINK: Destination of JFK inputted as ‘JFK’
# SYSTEMGUARD: 5000
#===============================================================================
# constants of source and sink nodes; LAX to JFK and of systemguard for a while
SOURCE = 'LAX'
SINK = 'JFK'
SYSTEMGUARD = 5000

flight_data = pd.read_csv('FLIGHT_DATA.csv') # import the data.

#start_time = timeit.default_timer()

# multiple directed graph as an input.
MultiG = nx.MultiDiGraph()
# edges for the graph.
for index, row in flight_data.iterrows():
    MultiG.add_edge(row['origin'], row['destination'], key=index,flightidx = index,
                    u=row['origin'],v=row['destination'], dep_time=row['departure_time'],
                    arr_time=row['arrival_time'], cap=row['capacity'], flow=0
                   )
#===============================================================================
# INPUT:
# FLIGHT_DATA.csv
# MultiDiGraph()
# add_edges()
# SOURCE: Origin of LAX inputted as ‘LAX’
# SINK: Destination of JFK inputted as ‘JFK’
# SYSTEMGUARD: 5000
#===============================================================================

#===============================================================================
# ALGORITHM STARTS
#===============================================================================

global Total_flow
Total_flow = 0      # initialize the Total_flow 0.
num_stops = 1       # number of stops -1 NOTE: 1 mean directed flight.
CombinedG = nx.Graph(MultiG)    # graph for the combined edges.
# checks list of the paths is empty.
MultiG, CombinedG, list_of_paths = check_stops(MultiG, CombinedG, num_stops)
# sorts the paths depending on the arrival times.
MultiG, path_of_recordednow, storage = timesorting(MultiG, list_of_paths)
foundmaxflow = False    # check if max-flow is found.
num_iterations = 0      # for estimate the number of iterations.
while foundmaxflow == False and num_iterations < SYSTEMGUARD:
    # initialize the nodes’ labels as ‘none’ and now as 00:00.
    num_iterations += 1
    for node in MultiG.nodes:
        MultiG.nodes[node]['label'] = 'none'
    now = pd.to_datetime('12:00 AM').strftime('%H:%M')
    shortest_path_list = list(path_of_recordednow.iloc[0,:-1])

    # finds if there is available paths.
    MultiG, found_path, list_of_edges, storage = check_avaiable_path(MultiG,
                                                shortest_path_list, now, storage)

    # if there is an available path
    if found_path == True:
        # updates min cost flow to each edge and augment the Total_flow.
        MultiG, Total_flow = min_cost_flow_updater(MultiG, shortest_path_list,
                                                    list_of_edges, Total_flow)

    # If there is but no available path, but if there is a path in the list of
    # paths with recorded arrival time
    if found_path == False and len(path_of_recordednow)!=0:
        # drops the used one.
        path_of_recordednow = path_of_recordednow.drop(path_of_recordednow.index[0])
    # If there is but no available path and there is no path in the list of paths
    # with recorded arrival time
    if found_path == False and len(path_of_recordednow) == 0:
        num_stops += 1
        # store all simple paths that have a length exactly equal to cutoff value
        MultiG, CombinedG, list_of_paths = check_stops(MultiG, CombinedG, num_stops)
        MultiG, path_of_recordednow, storage = timesorting(MultiG, list_of_paths)
        # If there is no available path in the list of the paths with incremented
        # intermediate nodes right after num_stops is incremented, stop iteration
        # of the while loop.
        if len(path_of_recordednow) == 0:
            foundmaxflow = True
#===============================================================================
# OUTPUT:
# Total_flow
# num_iterations
#===============================================================================
print('Max-flow:', Total_flow)
print('Number of iterations:', num_iterations)

#end_time = timeit.default_timer()
#print('Time Consumption:', end_time-start_time)
