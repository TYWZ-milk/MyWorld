function [ trees ] = calcu_midTrees( trees, s, e )
%CALC_MIDTREE Summary of this function goes here
%   Detailed explanation goes here
if e-s ==1
    return;
end

tree1 = trees{s};
tree2 = trees{e};

fp = fopen('my_two_trees.txt','w');
fprintf(fp,'%s\n', tree1);
fprintf(fp,'%s', tree2);
fclose(fp);

system('java -jar SturmMean.jar -n 20 -e 0.1 -o  midTree.txt my_two_trees.txt');

fp_2 = fopen('midTree.txt','r');
M = textscan(fp_2, '%s', 'delimiter', '\n', 'BufSize', 1000000);     %delimiterÊÇ¶¨½ç·û
mid_tree = M{1}{5};



mid = (e-s)/2 + s;
trees{mid} = mid_tree;
trees = calcu_midTrees(trees, s, mid);
trees = calcu_midTrees(trees, mid, e);



end

