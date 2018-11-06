#include "network.h"
#include "random.h"
#include <iostream>

void Network::resize(const size_t& new_size) {
	
	values.resize(new_size);
	clear_links();
	RNG.normal(values, 0, values.size());
	
}



bool Network::add_link(const size_t& a, const size_t& b) {
	
	if (a == b) {
		
		return false;
		
	}else if(std::max(a,b) >= values.size()) {
		
		return false;
		
	}else {
		
		std::vector<size_t> possible_values(neighbors(a));
		for (auto similar : possible_values) {
			if (similar == b) {return false; };
		}
		
	}
	
	links.insert(std::make_pair(a,b));
	links.insert(std::make_pair(b,a));
	return true;
	
}


size_t Network::random_connect(const double& mean_deg) {
	
	clear_links();
	std::vector<int> nodes_links(values.size());
	RNG.poisson(nodes_links,mean_deg);
	
	for (size_t i(0); i < nodes_links.size(); ++i) {
		
		bool created_all_links(nodes_links[i] == 0);
		double creating_links(0);
			
			while (!created_all_links) {
				
				if (add_link(i, RNG.uniform_double(0, values.size()))) {
					
					++creating_links;
					created_all_links = (nodes_links[i] == creating_links);
					
				}
			}
	}
	
	
	return (links.size()/2);
	
}	

size_t Network::set_values(const std::vector<double>& n_val) {
	
	size_t size(n_val.size());
	resize(size);
	values = n_val;
	return size;
	
}
	


size_t Network::size() const {
	
	return values.size();
	
}


size_t Network::degree(const size_t &_n) const {
	
	return links.count(_n);
	
}


double Network::value(const size_t &_n) const {
	
	if (!(_n > values.size())) {
		return values[_n];
	} else {
		return 1; // Error
	}
}


std::vector<double> Network::sorted_values() const {
	
	std::vector<double> sorted(values);
	std::sort(sorted.begin(), sorted.end(), std::greater<double>());
	return sorted;
}


std::vector<size_t> Network::neighbors(const size_t& n) const {

	 auto val = links.find(n);
	std::vector<size_t> all_neighbors;
	
	while(val->first == n) {
		
		all_neighbors.push_back(val->second);
		
		if (val == links.end()) {
		
			return all_neighbors;
			
		} else {
			
			++val;
		}
		
	}
	
	return all_neighbors; 
}

void Network::clear_links() {
	
	for (auto clear : links) {
		links.erase(clear.first);
	}
	
}


