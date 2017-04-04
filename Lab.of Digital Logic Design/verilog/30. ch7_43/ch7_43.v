module ch7_43(clk,init,x,z);
  parameter idle=0,l1=1,l2=2,l3=3,r1=4,r2=5,r3=6;
  input init,x,clk;
  output z;
  reg z;
  reg [2:0]state;
  always@(posedge clk)
  begin
    case(state)
      idle:
        if(init==1)
          z<=0;
        else
          if(x==0)
            state<=l1;
          else
            state<=r1;
      l1:
        if(init==1)
        begin
          z<=0;
          state<=idle;
        end
        else
          if(x==0)
            state<=l2;
          else
            state<=r1;
      l2:
        if(init==1)
        begin
          z<=0;
          state<=idle;
        end
        else
          if(x==0)
            state<=l2;
          else
            state<=l3;
      l3:
        if(init==1)
        begin
          z<=0;
          state<=idle;
        end
        else
          if(x==0)
            state<=l1;
          else
            z<=1;
      r1:
        if(init==1)
        begin
          z<=0;
          state<=idle;
        end
        else
          if(x==0)
            state<=l1;
          else
            state<=r2;
      r2:
        if(init==1)
        begin
          z<=0;
          state<=idle;
        end
        else
          if(x==0)
            state<=r3;
          else
            state<=r2;
      r3:
        if(init==1)
        begin
          z<=0;
          state<=idle;
        end
        else
          if(x==0)
            z<=1;
          else
            state<=r1;
    endcase
  end
endmodule