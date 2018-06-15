function trunk = RemoveSmallBranch(trunk)

%---
t_num = numel(trunk);
Len=[];
Ratio = [];
for i=1: numel(trunk{1}.children)
    if trunk{1}.children{i}.length ~= 0
        Len = [Len, trunk{1}.children{i}.length];
        cur_ratio = LengthCompute(trunk{1}.points, 1, i*5) / LengthCompute(trunk{1}.points, 1, size(trunk{1}.points, 1));
        Ratio = [Ratio, cur_ratio];
    end
end
poly_func1 = polyfit(Len, Ratio, 2);

LenEnd=[];
RatioEnd = [];
for i=1: numel(trunk{end}.children)
    if trunk{end}.children{i}.length ~= 0
        LenEnd = [LenEnd, trunk{end}.children{i}.length];
        cur_ratio = LengthCompute(trunk{end}.points, 1, i*5) / LengthCompute(trunk{end}.points, 1, size(trunk{end}.points, 1));
        RatioEnd = [RatioEnd, cur_ratio];
    end
end
poly_func2 = polyfit(LenEnd, RatioEnd, 2);

disp(['arrived here']);

for i=1 : t_num
    disp(['the stopped i is: ', i]);
    k = 1;
        
    for j=1: numel(trunk{i}.children)-1                     %最后一个不要动了
        cur_ratio = LengthCompute(trunk{i}.points, 1, j*5) / LengthCompute(trunk{i}.points, 1, size(trunk{i}.points, 1));
        L1 = polyval(poly_func1, cur_ratio);
        L2 = polyval(poly_func2, cur_ratio);
        
%         Max = max(L1, L2)+ abs(L2-L1)*0.5;
        Min = min(L1, L2)- abs(L2-L1)*0.5;
        
            
        if trunk{i}.children{j}.length < Min && i~=1 && i~= t_num
            trunk{i}.children{j}.isDeleted = 1;
        
        else
            trunk{i}.children{j}.isDeleted = 0;
            trunk{i}.n_children{k} = trunk{i}.children{j};
            k = k+1;
        end
    end

    trunk{i}.children{end}.isDeleted = 0;
    trunk{i}.n_children{k} = trunk{i}.children{end};
    k = k+1;
    
    
end
        
   
end



function len = LengthCompute(bifurcations, n , m)

len = 0;
for i=n:m-1
    len = len+ norm(bifurcations(i, 1:3) - bifurcations(i+1, 1:3));
end
end
    





