function [ T1, T2 ] = add_zero_branch( T1, T2 )
%ADD_ZERO_BRANCH Summary of this function goes here
%   Detailed explanation goes here

    child_num_1 = numel(T1.children);
    child_num_2 = numel(T2.children);

    % 如果T1的孩子数目大于T2的，则对于trunk2增加长度为O的孩子数， 反之亦然
    % 
    if child_num_1 > child_num_2
        trunk1 = T1; trunk2 = T2;
    elseif child_num_1 < child_num_2
        trunk1 = T2; trunk2 = T1;
    else
        return;
    end

        
    add_num = numel(trunk1.children) - numel(trunk2.children);
    non_len_num = floor(add_num/2);
    
   
    if ~isempty(trunk2.bifurcation)
        max_t = trunk2.bifurcation{end}.t_value;
        min_t = trunk2.bifurcation{1}.t_value;
        if max_t > min_t & trunk2.length ~=0
            new_t = min_t*trunk2.length : (max_t-min_t)/(add_num+1)*trunk2.length : max_t*trunk2.length;
        elseif max_t == min_t
            new_t = ones(1, add_num+2) * min_t*trunk2.length;
        else 
            new_t = zeros(1, add_num+2);
        end
        new_t_values = new_t(2:end-1);
        new_children = { };
        new_bifurcation = { };
        
        for i=1: numel(new_t_values)
            point = fnval(trunk2.SplineFunc, new_t_values(i));
            
            new_children{i}.father_branch_id = -1;
            new_children{i}.father_point_id = -1;
            new_children{i}.point(1).x = point(1);  new_children{i}.point(2).x = point(1);
            new_children{i}.point(1).y = point(2);  new_children{i}.point(2).y = point(2);
            new_children{i}.point(1).z = point(3);  new_children{i}.point(2).z = point(3);
            new_children{i}.point(1).r = 0;  new_children{i}.point(2).r = 0;
            new_children{i}.point(1).child = [];    new_children{i}.point(2).child = [];
            
            branch_data = [point(1), point(1); point(2), point(2); point(3), point(3); 0, 0];
            SplineFunc= cscvn(branch_data);
            
            new_children{i}.bifurcation = { };
            new_children{i}.children = { };
            new_children{i}.SplineFunc = SplineFunc;
            new_children{i}.length = 0;
                       
            new_bifurcation{i}.x = point(1);
            new_bifurcation{i}.y = point(2);
            new_bifurcation{i}.z = point(3);
            new_bifurcation{i}.r = 0;
            new_bifurcation{i}.child = -1;
            new_bifurcation{i}.origin_index = -1;
            new_bifurcation{i}.t_value = new_t_values(i)/trunk2.length;
        end
    
    
        new_num = numel(new_bifurcation);
        old_bifurcation = trunk2.bifurcation;

        old_num = numel(old_bifurcation);
        old_children = trunk2.children;

        i = 1;
        j = 1;
        k = 1;
        while i<=new_num && j<=old_num 
            if new_bifurcation{i}.t_value < old_bifurcation{j}.t_value
                trunk2.n_bifurcation{k} = new_bifurcation{i};
                trunk2.n_children{k} = new_children{i};
                k = k+1; i = i+1;
            else
                trunk2.n_bifurcation{k} = old_bifurcation{j};
                trunk2.n_children{k} = old_children{j};
                k = k+1; j = j+1;
            end
        end

        % 把剩余项写到trunk2.n_children和trunk2.n_bifurcation中
        if j<= old_num
            while j<= old_num
                trunk2.n_children{k} = old_children{j};
                trunk2.n_bifurcation{k} = old_bifurcation{j};
                k = k+1; j = j+1;
            end
        end
        
        if i<= new_num
            while i<= new_num
                trunk2.n_children{k} = new_children{i};
                trunk2.n_bifurcation{k} = new_bifurcation{i};
                k=k+1; i= i+1;
            end
        end
                
        trunk2.children = trunk2.n_children;
        trunk2.bifurcation = trunk2.n_bifurcation;

% 后处理
%             m = 0;
%             Layer1_c_num = numel(trunk1.children);
% 
%             for j=1: Layer1_c_num
%                 if trunk2.children{j}.length == 0 
%                     if m < non_len_num
%                         trunk2.children{j} = trunk1.children{j};
%                         m = m+1;
%                     else
%                         trunk1.children{j} = trunk2.children{j};
%                     end
%                 end
%             end


       if child_num_1 > child_num_2
            T1 = trunk1; T2 = trunk2;
       else
            T1 = trunk2; T2 = trunk1;
       end
   
       
    elseif trunk2.length ==0
        new_children = { };
        new_bifurcation = { };
        
        for i=1: add_num
            new_children{i}.father_branch_id = -1;
            new_children{i}.father_point_id = -1;
            new_children{i}.point(1).x = trunk2.point(1).x;  new_children{i}.point(2).x = trunk2.point(1).x;
            new_children{i}.point(1).y = trunk2.point(1).y;  new_children{i}.point(2).y = trunk2.point(1).y;
            new_children{i}.point(1).z = trunk2.point(1).z;  new_children{i}.point(2).z = trunk2.point(1).z;
            new_children{i}.point(1).r = 0;  new_children{i}.point(2).r = 0;
            new_children{i}.point(1).child = [];  new_children{i}.point(2).child = [];
            
            branch_data = [trunk2.point(1).x, trunk2.point(1).x; ...
                                    trunk2.point(1).y, trunk2.point(1).y;....
                                        trunk2.point(1).z, trunk2.point(1).z; ...
                                            0, 0];
                
            SplineFunc= cscvn(branch_data);
            
            new_children{i}.bifurcation = { };
            new_children{i}.children = { };
            new_children{i}.SplineFunc = SplineFunc;
            new_children{i}.length = 0;
                       
            new_bifurcation{i}.x = trunk2.point(1).x;
            new_bifurcation{i}.y = trunk2.point(1).y;
            new_bifurcation{i}.z = trunk2.point(1).z;
            new_bifurcation{i}.r = 0;
            new_bifurcation{i}.child = -1;
            new_bifurcation{i}.origin_index = -1;
            new_bifurcation{i}.t_value = i/(add_num+1);
              
        end
        
        trunk2.children = new_children;
        trunk2.bifurcation = new_bifurcation;
         
% % 后处理
% 
%             Layer1_c_num = numel(trunk1.children);
% 
%             for j=1: Layer1_c_num
%                 if trunk2.children{j}.length == 0
%                    if rand(1)< 0.5
%                        trunk1.children{j} = trunk2.children{j};
%                    else
%                        trunk2.children{j} = trunk1.children{j};
%                    end
%                 end
%             end

        if child_num_1 > child_num_2
            T1 = trunk1; T2 = trunk2;
        else
            T1 = trunk2; T2 = trunk1;
        end
        
    else
        new_children = { };
        new_bifurcation = { };
        
        new_t = 0 : 1/(add_num+1)*trunk2.length : 1*trunk2.length;
        new_t_values = new_t(2:end-1);
            
        for i=1: numel(new_t_values)
            point = fnval(trunk2.SplineFunc, new_t_values(i));
            
            new_children{i}.father_branch_id = -1;
            new_children{i}.father_point_id = -1;
            new_children{i}.point(1).x = point(1);  new_children{i}.point(2).x = point(1);
            new_children{i}.point(1).y = point(2);  new_children{i}.point(2).y = point(2);
            new_children{i}.point(1).z = point(3);  new_children{i}.point(2).z = point(3);
            new_children{i}.point(1).r = 0;  new_children{i}.point(2).r = 0;
            new_children{i}.point(1).child = [];  new_children{i}.point(2).child = [];
            
            branch_data = [point(1), point(1); point(2), point(2); point(3), point(3);0, 0];
            SplineFunc= cscvn(branch_data);
            
            new_children{i}.bifurcation = { };
            new_children{i}.children = { };
            new_children{i}.SplineFunc = SplineFunc;
            new_children{i}.length = 0;
            
           
                       
            new_bifurcation{i}.x = point(1);
            new_bifurcation{i}.y = point(2);
            new_bifurcation{i}.z = point(3);
            new_bifurcation{i}.r = 0;
            new_bifurcation{i}.child = -1;
            new_bifurcation{i}.origin_index = -1;
            new_bifurcation{i}.t_value = new_t_values(i)/trunk2.length;
        end
    
        trunk2.children = new_children;
        trunk2.bifurcation = new_bifurcation;

% % 后处理
% 
%     Layer1_c_num = numel(trunk1.children);
% 
%     for j=1: Layer1_c_num
%         if trunk2.children{j}.length == 0
%            if rand(1)< 0.5
%                trunk1.children{j} = trunk2.children{j};
%            else
%                trunk2.children{j} = trunk1.children{j};
%            end
%         end
%     end
        
       if child_num_1 > child_num_2
            T1 = trunk1; T2 = trunk2;
       else
            T1 = trunk2; T2 = trunk1;
       end
       
    end
  
end


