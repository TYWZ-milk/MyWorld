function [ trunk ] = collect_uv_coord( trunk )

trunk.uv_collection = [];

for i=1: numel(trunk.uv_coord)
    trunk.uv_collection = [trunk.uv_collection; trunk.uv_coord{i}];
end

end

