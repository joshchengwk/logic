/* Copyright 2017 Tymoteusz Blazejczyk
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

module logic_clock_domain_crossing_generic_write_sync #(
    int ADDRESS_WIDTH = 1
) (
    input read_aclk,
    input read_areset_n,
    input [ADDRESS_WIDTH-1:0] read_pointer,
    input write_aclk,
    input write_areset_n,
    output logic [ADDRESS_WIDTH-1:0] read_pointer_synced
);
    logic_clock_domain_crossing_generic_read_sync #(
        .ADDRESS_WIDTH(ADDRESS_WIDTH)
    )
    synced (
        .write_aclk(read_aclk),
        .write_areset_n(read_areset_n),
        .write_pointer(read_pointer),
        .read_aclk(write_aclk),
        .read_areset_n(write_areset_n),
        .write_pointer_synced(read_pointer_synced)
    );
endmodule
