
function show_txtskl_file_data(branch, branch_num)

figure;
view(0, -90);
set(gcf,'color','white');
axis equal;
box off;
hold on;
xlabel('X axis');
ylabel('Y axis');
zlabel('Z axis');

% i��ʾ����
for i = 1: 4%size(branch, 1)
    for j = 1:branch_num(i)
        point_num = length(branch(i,j).point);
        clear point_x point_y point_z;
        point_x = [];
        point_y = [];
        point_z = [];
        
        for k = 1: point_num
            point_x = [point_x, branch(i,j).point(k).x];
            point_y = [point_y, branch(i,j).point(k).y];
            point_z = [point_z, branch(i,j).point(k).z];
        end
        
        if i == 1
            line_handle = plot3(point_x, point_y, point_z, 'r','LineWidth', 3);
            set(line_handle, 'linesmoothing', 'on');
            hold on;
        end
        if i == 2
            line_handle = plot3(point_x, point_y, point_z, 'g','LineWidth', 3);
            set(line_handle, 'linesmoothing', 'on');
            hold on;
        end
        if i == 3
            line_handle = plot3(point_x, point_y, point_z, 'b','LineWidth', 3);
            set(line_handle, 'linesmoothing', 'on');
            hold on;
        end
        
        if i == 4
            line_handle = plot3(point_x, point_y, point_z, 'k','LineWidth', 3);
            set(line_handle, 'linesmoothing', 'on');
            hold on;
        end
        
        if i == 5
            line_handle = plot3(point_x, point_y, point_z, 'c','LineWidth', 3);
            set(line_handle, 'linesmoothing', 'on');
            hold on;
        end
        
    end
end
end