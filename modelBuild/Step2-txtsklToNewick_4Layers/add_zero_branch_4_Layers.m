function [ T1, T2 ] = add_zero_branch_4_Layers( T1, T2 )
%ADD_ZERO_BRANCH_4LAYERS Summary of this function goes here
%   Detailed explanation goes here

[T1, T2] = add_zero_branch(T1, T2);

child_num = numel(T1.children);

for i=1: child_num
    clear T;
    T{1} = T1.children{i};
    T{2} = T2.children{i};
    
    T = add_zero_branch_multi(T);
    
    T1.children{i} = T{1};
    T2.children{i} = T{2};
end

end

