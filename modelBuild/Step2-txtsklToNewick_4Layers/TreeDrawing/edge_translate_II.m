function [ my_branch ] = edge_translate_II( myend, start, my_branch,len )
%TRAN Summary of this function goes here
%   Detailed explanation goes here
%   my_branch��һ���ṹ�����飬���
%   end�ǽṹ�壬��ƽ��������ĩ�ˣ�startҲ�ǽṹ�壬��ƽ��������ʼ��
 trans_vector = [myend(1) - start(1), myend(2) - start(2), myend(3) - start(3)];
 for i = 1: len
     my_branch(i, 1) = my_branch(i, 1) + trans_vector(1);
     my_branch(i, 2) = my_branch(i, 2)+ trans_vector(2);
     my_branch(i, 3) = my_branch(i, 3) + trans_vector(3);
 end

end

