`timescale 1ns / 1ps

module MAC (
    input clk,
    input rst,
    input mac_enable,
    input [7:0] A,
    input [7:0] B,
    output [15:0] LED,
    output reg oflow
);

reg [31:0] dot_product;

always @(posedge clk) begin
    oflow <= (dot_product > 16'hFFFF) ? 1'b1 : 1'b0;
end

always @(posedge clk) begin
    if (rst) begin
        dot_product <= 0;
    end

    else if (mac_enable) begin
        dot_product <= dot_product + (A * B);
    end
end

assign LED = (~oflow) ? dot_product[15:0] : 16'd0;

endmodule
