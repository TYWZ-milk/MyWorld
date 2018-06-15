function write_newick_file(file_name,tree_1, tree_2);
    fp_w = fopen(file_name, 'w');
    fprintf(fp_w, '%s\n', tree_1);
    fprintf(fp_w, '%s', tree_2);
end