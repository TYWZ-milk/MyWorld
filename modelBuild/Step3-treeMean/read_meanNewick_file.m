function [tree_data] = read_meanNewick_file (file_name)
    fp_1 = fopen(file_name, 'r');
    T = textscan(fp_1, '%s', 'delimiter', '\n', 'BufSize', 100000);
    tree_data = T{1}{5,1};
end