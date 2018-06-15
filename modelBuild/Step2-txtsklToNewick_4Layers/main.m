clear all;
addpath TreeDrawing;

folder_name = 'txtskl_data';
F = ls([folder_name,'\*.txtskl']);
for i=1: size(F, 1)
    s =  F(i, :);
    s(find(isspace(s))) = [];
    Files{i} = s;
end
% break;

F1_ind = 12;
F2_ind = 2;

% Read the txtskl file
[branch1, branch_num1] = ReadSkelFile([folder_name, '\', Files{F1_ind}]);
[branch2, branch_num2] = ReadSkelFile([folder_name, '\', Files{F2_ind}]);

% Add the 4-th layers manually if the layer_num = 3
if numel(branch_num1) == 3  
    branch1(4, 1) = branch1(3, 1);
    branch_num1(4) = 0;
end

if numel(branch_num2) == 3  
    branch2(4, 1) = branch2(3, 1);
    branch_num2(4) = 0;
end

% show the txtskl file 
show_txtskl_file_data(branch1, branch_num1);
show_txtskl_file_data(branch2, branch_num2);
% break;
%%
% Transform the tree to trunk-representation just for easy-management, but
% here we only get 3 layers this moment
trunk1 = TrunkStruction(branch1, branch_num1);
trunk2 = TrunkStruction(branch2, branch_num2);
% break;

% Add the 4th layer to trunk1 and trunk2.
trunk1 = Add4thLayer(trunk1, branch1);
trunk2 = Add4thLayer(trunk2, branch2);

%%
% add zero-length branches to the two trees
[trunk1, trunk2] = add_zero_branch_4_Layers(trunk1, trunk2);

% Now start labeling, the labelling process is the forming correspondence process 
[trunk1, trunk2] = Labeling_4_Layers(trunk1, trunk2);

% Transform the trunk-representation to the newick string  
disp(['start transforming the trees']);
[array_phytree_1, newick_str1] = Trunk2array_phytree_4_Layers( trunk1 );
disp(['the first tree transformation is finished']);
% break;

disp(['start transforming the trees']);
[array_phytree_2, newick_str2] = Trunk2array_phytree_4_Layers( trunk2 );
disp(['the second tree transformation is finished']);
% break;

% Show the trees of newick string representation
% figure;
% set(gcf,'color','white'); axis equal; box on; hold on;
% title([Files{F1_ind} ': After transform to newick']);
% ShowWholeAirway_II(newick_str1, 0, 0, 0);
% 
% figure;
% set(gcf,'color','white'); axis equal; box on; hold on;
% title([Files{F2_ind} ': After transform to newick']);
% ShowWholeAirway_II(newick_str2, 0, 0, 0);

%%
% Write the two trees (two newick strings) into a file
fp_3 = fopen(['Trees_', 'T', num2str(F1_ind), '_T', num2str(F2_ind), '.newick'], 'w'); %'__',Files{F3_ind}(1: end-7), '__', Files{F4_ind}(1: end-7)
fprintf(fp_3, '%s',['(' newick_str1 ')']);
fprintf(fp_3, '\n');
fprintf(fp_3, '%s',['(' newick_str2 ')']);
fclose(fp_3);