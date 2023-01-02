close all;
clear ;

% load settings
 st = parameter_settings();

 st.alpha = 0.01;% 
 st.lambda = 0.08; % the weight of the data term 
 st.pyramid_factor = 0.8;% 
 st.warps = 5; % the numbers of warps per level 
 st.max_its = 10; % the number of equation iterations per warp 
 
show_flow =1; % 1 = display the evolution of the flow, 0 = do not show
h = figure('Name', 'Optical flow');
   
I1 = double(imread('data/RubberWhale/frame10.png'))/255;
I2 = double(imread('data/RubberWhale/frame11.png'))/255; 
floPath = 'data/RubberWhale/flow10.flo';

tic
% call main routine
[flow, Numu, Numv, Numc] = coarse_to_fine(I1, I2, st, show_flow, h);
toc
u = flow(:, :, 1);
v = flow(:, :, 2);

%% evalutate the correctness of the computed flow
% read the ground-truth flow
realFlow = readFlowFile(floPath);
tu = realFlow(:, :, 1);
tv = realFlow(:, :, 2);

flowImg0 = uint8(robust_flowToColor(realFlow));
figure; imshow(flowImg0);
% compute the mean end-point error (mepe) and the mean angular error (mang)
UNKNOWN_FLOW_THRESH = 1e9;
[mang, mepe] = flowError(tu, tv, u, v, ...
  0, 0.0, UNKNOWN_FLOW_THRESH);
disp(['Mean end-point error: ', num2str(mepe)]);
disp(['Mean angular error: ', num2str(mang)]);

% display the flow
flowImg = uint8(robust_flowToColor(flow));
figure; imshow(flowImg);

