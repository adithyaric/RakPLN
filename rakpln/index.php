<?php include "koneksi.php"; ?>
<?php include "header.php"; ?>

<h1 class="text-center">Material Gudang PT. PLN (Persero)</h1>
<h3 class="text-center">By : Mantab Jiwa</h3>
<hr>

<div class="text-center">
	<a type="button" class="btn btn-primary mr-2" href="tambah_barang.php">Tambah <i class="fa fa-plus"></i></a>
	<a type="button" class="btn btn-success mr-2" href="ambil_barang.php">Ambil Barang <i class="fa fa-search"></i></a>
	<!-- <a type="button" class="btn btn-warning mr-2" href="update_barang.php">Update Barang</a> -->
	<!-- <a type="button" class="btn btn-danger mr-2" href="hapus_barang.php">Hapus Barang</a> -->
</div>

<br>

<table class="table table-bordered">
	<thead style="vertical-align: middle;">
		<tr>
			<th class="text-center" width="50px">No</th>
			<th class="text-center" width="50px">ID</th>
			<th class="text-center" width="150px">Tanggal</th>
			<th class="text-center" width="100px">Status</th>
			<th class="text-center" width="100px">Nama barang</th>
			<th class="text-center" width="100px">Jumlah</th>
			<th class="text-center" width="100px">Kode Rak</th>
			<th class="text-center" width="100px">Aksi</th>
		</tr>
	</thead>

	<tbody>
		<?php
		$no = 1;
		$data_statistik = $koneksi->query("SELECT * FROM tb_statistik");
		$jumlah_data = $data_statistik->num_rows;

		if ($jumlah_data > 0) {
			while ($pecah = $data_statistik->fetch_assoc()) {
		?>
				<tr>
					<td class="text-center" width="30px"><?php echo $no; ?></td>
					<td class="text-center" width="30px"><?php echo $pecah['id']; ?></td>
					<td><?php echo $pecah['tgl_update']; ?></td>
					<td><?php echo $pecah['status_update']; ?></td>
					<td><?php echo $pecah['nama_barang']; ?></td>
					<td><?php echo $pecah['jumlah_barang'] . " " . $pecah['satuan_barang']; ?></td>
					<td><?php echo $pecah['kode_rak']; ?></td>
					<td>
						<a type="button" class="btn btn-warning mr-2" href="update_barang.php?id=<?php echo $pecah['id']; ?>">
							Edit <i class="fa fa-edit"></i></a>
						<a type="button" class="btn btn-danger mr-2" href="hapus_barang.php?id=<?php echo $pecah['id']; ?>">
							Hapus <i class="fa fa-trash"></i></a>
					</td>
				</tr>

			<?php
				$no++;
			}
		} else {
			?>

			<tr>
				<td colspan="6">
					<center>Data tidak ditemukan !</center>
				</td>
			</tr>

		<?php
		}
		?>

	</tbody>
</table>

<?php include "footer.php"; ?>