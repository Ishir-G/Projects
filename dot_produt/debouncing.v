`timescale 1ns / 1ps

module Debouncing(
    input clk,
    input noisy_in,
    output reg clean_out
    );

    reg [3:0] count;
    reg noisy_in_sync;

    initial begin
        clean_out = 32'd0;
        count = 4'd0;
    end
    
    always @(posedge clk) begin
        noisy_in_sync <= noisy_in;

        if(~(noisy_in_sync == clean_out)) begin
            count = count + 1;

            if(count >= 2) begin
                clean_out = noisy_in_sync;
                count = 0;
            end
        end
        else begin
            count = 0;
        end

    end

endmodule
