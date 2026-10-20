#include "face_finder.h"

#include <map>
#include <algorithm>

std::vector<Face> FaceFinder::find_faces(const std::vector<Point>& points, const std::vector<Edge>& edges)
{
    std::vector<Face> faces;

    std::map<int, std::vector<int>> adj;
    for (const auto& edge : edges)
    {
        adj[edge.get_start()].push_back(edge.get_end());
        adj[edge.get_end()].push_back(edge.get_start());
    }
    for (auto& pair : adj)
        std::sort(pair.second.begin(), pair.second.end());

    std::vector<std::vector<int>> processed_faces;

    for (const auto& edge : edges)
    {
        int v1 = edge.get_start(), v2 = edge.get_end();
        for (int v3 : adj[v2])
        {
            if (v3 == v1) 
                continue;
            for (int v4 : adj[v3])
            {
                if (v4 == v2 || v4 == v1) 
                    continue;
                if (std::binary_search(adj[v4].begin(), adj[v4].end(), v1))
                {
                    std::vector<int> face_ids = {v1, v2, v3, v4};
                    std::sort(face_ids.begin(), face_ids.end());
                    bool is_new = true;
                    for (const auto& p : processed_faces)
                        if (p == face_ids) 
                        { 
                            is_new = false; 
                            break; 
                        }
                        
                    if (is_new)
                    {
                        processed_faces.push_back(face_ids);
                        faces.push_back({{points[v1], points[v2], points[v3], points[v4]}});
                    }
                }
            }
        }
    }
    return faces;
}