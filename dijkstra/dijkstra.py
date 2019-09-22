import sys

try:
	file_name = sys.argv[1]
	graph = open(file_name, "r")
except Exception as e:
	print "[" + str(e) + "]"
	print "Text file containing graph not provided. Exiting the script."
else:
	edges = []
	visited = []
	aux_visited = []
	unvisited = []

	for line in graph:
		aux = []
		for ch in line:
			if (ch != ' ' and ch != '\n'):
				aux.append(int(ch))
		edges.append({'a': aux[0], 'b': aux[1], 'dist': aux[2]})
		if (aux[0] not in aux_visited):
			aux_visited.append(aux[0])
		if (aux[1] not in aux_visited):
			aux_visited.append(aux[1])

	aux_visited.sort()

	for vis in aux_visited:
		unvisited.append({'node': vis, 'calc_dist': sys.maxsize})

	unvisited[0]['calc_dist'] = 0
	min_dist_index = 0
	current_vertex = unvisited[min_dist_index]['node']

	while (len(visited) != len(unvisited)):
		new_dist_aux = sys.maxsize
		for neighbor in edges:
			if (neighbor['a'] == current_vertex):
				new_dist = 0
				if (neighbor['b'] not in visited):
					for edge in edges:
						if (edge['a'] == current_vertex and edge['b'] == neighbor['b']):
							new_dist = edge['dist'] + unvisited[current_vertex]['calc_dist']
					if (new_dist < unvisited[neighbor['b']]):
						unvisited[neighbor['b']]['calc_dist'] = new_dist


			if (neighbor['b'] == current_vertex):
				new_dist = 0
				if (neighbor['a'] not in visited):
					for edge in edges:
						if (edge['b'] == current_vertex and edge['a'] == neighbor['a']):
							new_dist = edge['dist'] + unvisited[current_vertex]['calc_dist']
					if (new_dist < unvisited[neighbor['a']]):
						unvisited[neighbor['a']]['calc_dist'] = new_dist

		visited.append(current_vertex)

		aux_next_current = sys.maxsize
		for cur in unvisited:
			if (cur['node'] not in visited):
				if (cur['calc_dist'] < aux_next_current):
					aux_next_current = cur['calc_dist']
					min_dist_index = cur['node']
		current_vertex = unvisited[min_dist_index]['node']

	print "Shortest path betweem any two vertices: "
	print visited

