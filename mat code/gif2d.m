s =0.2; x1=0;                     %  ȷ����ʼ�������x1��������
    nframes = 50;                    %  ȷ��������֡��
    for k = 1:nframes
        x1= x1+s;                       %  ȷ����ͼʱ��������ֵֹx1
        x =0:0.01:x1; y =sin(x);
        plot(x,y);                         %  ��x=[0 x1]��y=sin(x)����
        axis([0 2*pi -1 1])            % ���������᷶Χ
        grid off                             % ����ʾ������
        M(k) = getframe;             %  ����ǰͼ�δ������M(k)
    end
    movie(M,3)                         %  �ظ�3�β��Ŷ���M