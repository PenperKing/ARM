s =0.2; x1=0;                     %  确定起始点横坐标x1及其增量
    nframes = 50;                    %  确定动画总帧数
    for k = 1:nframes
        x1= x1+s;                       %  确定画图时横坐标终止值x1
        x =0:0.01:x1; y =sin(x);
        plot(x,y);                         %  在x=[0 x1]作y=sin(x)曲线
        axis([0 2*pi -1 1])            % 定义坐标轴范围
        grid off                             % 不显示网格线
        M(k) = getframe;             %  将当前图形存入矩阵M(k)
    end
    movie(M,3)                         %  重复3次播放动画M