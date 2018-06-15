function [tree_Ito_V ] = calcuOneLineTree( tree_I, tree_V )
write_newick_file('tree_Itree_V.txt', tree_I, tree_V)

system('java -jar SturmMean.jar -n 10 -e 0.01 -o tree_III.txt tree_Itree_V.txt');
tree_III = read_meanNewick_file('tree_III.txt');  %读java所产生的平均树文件

%--------------------------------------------------------------------------
write_newick_file('tree_Itree_III.txt', tree_I, tree_III)

system('java -jar SturmMean.jar -n 10 -e 0.01 -o tree_II.txt tree_Itree_III.txt');
tree_II = read_meanNewick_file('tree_II.txt');  %读java所产生的平均树文件

%--------------------------------------------------------------------------
write_newick_file('tree_IIItree_V.txt', tree_III, tree_V)

system('java -jar SturmMean.jar -n 10 -e 0.01 -o tree_IV.txt tree_IIItree_V.txt');
tree_IV = read_meanNewick_file('tree_IV.txt');  %读java所产生的平均树文件


tree_Ito_V = [{tree_I}, {tree_II}, {tree_III}, {tree_IV}, {tree_V}];
end

