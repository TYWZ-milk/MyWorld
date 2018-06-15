function cost = calcu_branch_dif( branch1, branch2 )
%CALCU_BRANCH_DIF Summary of this function goes here
%   Detailed explanation goes here

branch_data1=[branch1.point.x; branch1.point.y; branch1.point.z; branch1.point.r];
branch_data2=[branch2.point.x; branch2.point.y; branch2.point.z; branch2.point.r];

%��ÿ��branch��������ֵ���
SplineFunc1 = cscvn(branch_data1);      %�����i��branch����Ϻ���
size_p = size(SplineFunc1.breaks,2);   %��¼���Ƶ����Ŀ
length = SplineFunc1.breaks(size_p);   %�������
sample = 0:length/10:length;           %�����������,����ɳ�101����
spline_data1 = fnval(SplineFunc1, sample);

%��ÿ��branch��������ֵ���
SplineFunc2 = cscvn(branch_data2);      %�����i��branch����Ϻ���
size_p = size(SplineFunc2.breaks, 2);   %��¼���Ƶ����Ŀ
length = SplineFunc2.breaks(size_p);   %�������
sample = 0:length/10:length;           %�����������,����ɳ�101����
spline_data2 = fnval(SplineFunc2, sample);

spline_data1 = spline_data1';
spline_data2 = spline_data2';
%% algin the two branches;

    fpoint1 = spline_data1(1, 1:3);
    fpoint2 = spline_data2(1, 1:3);
    
    for m = 1 : size(spline_data1, 1)
        spline_data1(m, 1:3) = spline_data1(m, 1:3) - fpoint1;
    end
    
    for m = 1 : size(spline_data2, 1)
        spline_data2(m, 1:3) = spline_data2(m, 1:3) - fpoint2;
    end
    
    
        

 %***���߶�����������㷨
        A = spline_data1(:, 1:3)'* spline_data2(:, 1:3);   
        [u,s,v] = svd(A);
        O = u * v';
        spline_data2(:, 1:3) = (O * spline_data2(:, 1:3)')';
 %***
%  figure;
%  plot3(spline_data1(:, 1), spline_data1(:, 2), spline_data1(:, 3), 'r', 'LineWidth', 2); hold on;
%  plot3(spline_data2(:, 1), spline_data2(:, 2), spline_data2(:, 3), 'b', 'LineWidth', 2); hold on;
 
%%
sample_num = size(spline_data2, 1);

cost = 0;
for i = 1: sample_num
    vector4 = spline_data1(i, :) - spline_data2(i, :);
    cost = cost + norm(vector4);
end

save spline_data
   

end

