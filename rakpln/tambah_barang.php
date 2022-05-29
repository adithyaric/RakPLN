<?php include "koneksi.php"; ?>
<?php include "header.php"; ?>

<h1 class="text-center">Tambah Material</h1>
<hr>

<form enctype="multipart/form-data" method="POST" class="needs-validation" novalidate>
	<div class="container">
		<table class="table table-bordered table-hover">
			<tbody>
				<tr>
					<td width="150px">Nama Material</td>
					<td><input type="text" class="form-control" name="nama_barang" placeholder="Masukkan Nama Material" required></td>
				</tr>

				<tr>
					<td>Jumlah Material</td>
					<td><input type="number" class="form-control" name="jumlah_barang" placeholder="Masukkan Jumlah Material" required></td>
				</tr>

				<tr>
					<td>Satuan Material</td>
					<td><input type="text" class="form-control" name="satuan_barang" placeholder="Masukkan Satuan Material" required></td>
				</tr>

				<tr>
					<td>Pin Led</td>
					<td><input type="number" class="form-control" name="pin_led" placeholder="Masukkan pin led" required></td>
				</tr>

				<tr>
					<td>Kode Rak Material</td>
					<td>
						<div class="input-group">
							<input type="text" class="form-control mr-5" name="rak_baris" placeholder="Baris" required>
							<input type="text" class="form-control" name="rak_kolom" placeholder="Kolom" required>
						</div>
					</td>
				</tr>
			</tbody>
		</table>
	</div>

	<br>

	<p style="text-align: center;">
		<button class="btn btn-primary mr-2" name="simpan_barang">Simpan</button>
		<a type="button" class="btn btn-danger mr-2" href="index.php">Batal</a>
	</p>

</form>

<style type="text/css">
	.table {
		margin: 0 auto;
		width: auto;
	}
</style>

<?php

if (isset($_POST['simpan_barang'])) {
	$nama_barang = $_POST['nama_barang'];
	$jumlah_barang = $_POST['jumlah_barang'];
	$pin_led = $_POST['pin_led'];
	$satuan_barang = $_POST['satuan_barang'];
	$rak_baris = $_POST['rak_baris'];
	$rak_kolom = $_POST['rak_kolom'];
	$kode_rak = $rak_kolom . $rak_baris;

	if (!empty($nama_barang) || !empty($jumlah_barang) || !empty($satuan_barang) || !empty($rak_baris) || !empty($rak_kolom) || !empty($pin_led)) {

		$data = $koneksi->query("SELECT * FROM tb_statistik WHERE nama_barang='$nama_barang'");
		$jmldata = $data->num_rows;
		// $pecahan = $data->fetch_assoc();
		// $jml = $pecahan['jumlah_barang'];

		if (!$jmldata > 0) {
			$koneksi->query("INSERT INTO tb_statistik (status_update, nama_barang, jumlah_barang, satuan_barang, kode_rak, pin_led) VALUES ('Baru', '$nama_barang', '$jumlah_barang', '$satuan_barang', '$kode_rak', '$pin_led')");
			echo "<script>alert('Material baru berhasil ditambahkan !');</script>";
			echo "<script>location='index.php';</script>";
		} else {
			// $hasil = $jml + (int)$jumlah_barang;
			// $koneksi->query("UPDATE tb_statistik SET status_update = 'Update', nama_barang = '$nama_barang',  satuan_barang = '$satuan_barang', jumlah_barang = '$hasil', kode_rak = '$kode_rak' WHERE nama_barang = '$nama_barang'");
			echo "<script>alert('Barang Sudah ada !');</script>";
			echo "<script>location='index.php';</script>";
		}
	} else {
		echo "<script>alert('Mohon lengkapi semua data !');</script>";
	}
}

?>

<?php include "footer.php"; ?>