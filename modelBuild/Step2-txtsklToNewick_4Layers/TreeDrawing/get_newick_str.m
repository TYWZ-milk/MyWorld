function str = get_newick_str(tr, boot)
% �õ�tr�� boot��newick format data 

if numel(tr)~=1
     error('Bioinfo:phytree:getstr:NoMultielementArrays',...
           'Phylogenetic tree must be an 1-by-1 object.');
end

%�õ�phytree tr��������Ϣ���浽V��
V = get(tr);
numBranches = V.NumBranches;
numLeaves = numBranches + 1;
numLabels = numBranches + numLeaves;    % numLabelsͳ�����нڵ㣨Ҷ��&��Ҷ�ӣ�������

label_name = V.NodeNames;   %���е�label�ļ���

for i = 1:numLabels;
    % �����Ҷ�ӽڵ㣬��Ҫд������ı�ţ�R1��L1�ȣ�
    if i<=numLeaves        
        node_info{i} = [label_name{i} ':' '[' boot{i} ']'];
    else
        node_info{i} = [':' '[' boot{i} ']']; 
    end

end

%tree_str �洢���Ǹ���ѭ��������newick��ʽ���ݣ����һ������������newick��ʽ
tree_str = cell(1,10000);
for i = 1:numBranches
    if V.Pointers(i,1) > numLeaves
        t1 = tree_str{ V.Pointers(i,1) };
    else
        t1 = node_info{ V.Pointers(i,1) };
    end
    
    if V.Pointers(i,2) > numLeaves
        t2 = tree_str{ V.Pointers(i,2) };
    else
        t2 = node_info{ V.Pointers(i,2) };
    end

    tree_str{i  +numLeaves} = [ '(' t1 ',' t2 ')' node_info{i+numLeaves} ]; 
end

str = sprintf(tree_str{numLabels});

end

