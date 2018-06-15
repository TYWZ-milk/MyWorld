clear;
addpath TreeDrawing;

file_name = 'Trees_T12_T2.newick';
fp_1 = fopen(file_name,'r');
% read the file
T = textscan(fp_1, '%s', 'delimiter', '\n', 'BufSize', 10000000);

tree_1 = T{1}{1};
tree_9 = T{1}{2};

trees = cell(1, 9);
trees{1} = tree_1;
trees{9} = tree_9;

tic;
% start computing the tree sequence.
trees = calcu_midTrees(trees, 1 , 9);
toc;
% break;
% -------------------------------------------------------------------------
% % show all the trees.
% figure('color', 'w','Position',[100,100,1800,200]);
% axis equal;  hold on;
% axis off;  hold on;
% % axis([-5, 60, 0, 5,0, 5]); hold on
% view([0, -90]);
% 
% for i=1:5
% % %     figure('color', 'w','Position',[100,100,800,600]);
% % %     axis equal;  hold on;
% % %     axis on;  hold on;
% % %     axis([-5, 60, 0, 5,0, 5]); hold on
% %     ShowWholeAirway_II(trees{i}, (i-1)*1, 0, 0); hold on; 
% end
% break;


%% 
% make the directory of the tree sequence file
addpath GetOBJ
mkdir([file_name(1: end-7), '_Seq']);
disp('Start transforming the newick to obj');

for i=1:9
    if i~= 400
    trunk{i} = Newick2Obj(trees{i}, [[file_name(1: end-7), '_Seq'],'\',file_name(1: end-7), '_t', num2str(i)], (i-1)*[0, 0, 0]);
    end
end









